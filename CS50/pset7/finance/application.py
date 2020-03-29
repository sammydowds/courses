import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required


def index():
    """Show portfolio of stocks"""

    #saving the user info
    user_id = session["user_id"]

    #pulling data from the database in regards to stock info
    rows = db.execute("SELECT symbol, name, shares FROM portfolio WHERE id = :user_id", user_id = user_id)

    #defining new price of stock here and updating dictionary with price and total value
    for row in rows:
        stock_info = lookup(row['symbol'])
        shares = row['shares']
        price = (stock_info['price'])
        row['price'] = usd(price)
        row['total'] = usd(price * shares)

    #saving current amount of cash available
    cash_user = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = user_id)[0]

    #convert to USD
    cash_user = usd(cash_user['cash'])

    #render table of stocks owned and cash in one table
    return render_template("index.html", user_info = rows, cash = cash_user)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    buy = 'bought'
    if request.method == "POST":

        #check if form is empty or invalid input for stock symbols
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("Please enter valid symbol")
        #check if number field is empty
        elif not request.form.get("shares") or int(request.form.get("shares")) < 0:
            return apology("Please enter a number")

        else:
            #store user id currently logged in for accessing this users data in the database
            user_id = session["user_id"]

            #saving the stock price per share in a integer
            stock_price_share = int(lookup(request.form.get("symbol"))["price"])

            #storing stock name
            stock_name = (lookup(request.form.get("symbol"))["name"])

            #saving number from form as an int
            number_stocks = int(request.form.get("shares"))

            #multiplying number of stocks desired by price per stock
            total_cost = int(stock_price_share) * number_stocks

            #query to database to save current cash on hand
            current_cash = (db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = user_id))
            current_cash = current_cash[0]['cash']

            #checking if the total cost of shares is more than you have available, if so - then rendering message template
            if current_cash < total_cost:
                return apology("Sorry bruh, you too broke for dat lyfe", 400)
            else:
                #else we are going to update the cash value in the database of users
                updated_cash = current_cash - total_cost
                db.execute("UPDATE users SET cash = :updated_cash WHERE id = :user_id", updated_cash = updated_cash, user_id = user_id)

            #check if portfolio exists in portfolio
            check = db.execute("SELECT symbol FROM portfolio WHERE symbol = :symbol AND id = :user_id", symbol = request.form.get("symbol"), user_id = user_id)

            #if stock exists in portfolio then update the amount of shares owned
            if check:
                db.execute("UPDATE portfolio SET shares = shares + :shares WHERE id = :user_id AND symbol = :symbol", shares = number_stocks, user_id = user_id, symbol = request.form.get("symbol"))

            else:
                #create row in portfolio for this stock
                db.execute("INSERT INTO 'portfolio' ('symbol', 'name', 'shares', 'id') VALUES (:symbol, :name, :shares, :user_id)", symbol = request.form.get("symbol"), name = stock_name, shares = number_stocks, user_id = user_id)


            #getting date and updating database for history with static values
            date = str(datetime.datetime.now())
            print(date)

            #inserting line into history database for this purchase
            db.execute("INSERT INTO 'history' ('id', 'type', 'symbol', 'shares', 'price', 'total', 'date_time', 'name') VALUES (:user_id, :transaction, :symbol, :shares, :price, :total, :date_time, :name)", user_id = user_id, transaction = buy, \
            symbol = request.form.get("symbol").upper(), shares = number_stocks, price = usd(stock_price_share), total = usd(total_cost), date_time = date, name = stock_name)

            #pulling data for bought in
            bought_hist = db.execute("SELECT type, symbol, shares, price, total, date_time, name FROM history WHERE type = 'bought' AND id = :user_id", user_id = user_id)

            #returning a filtered history list for "bought" records
            return render_template("history.html", history = bought_hist)

    else:
        return render_template("buy.html")





@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    hist = db.execute("SELECT * FROM history WHERE id = :user_id", user_id = user_id)
    return render_template("history.html", history = hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""


    if request.method == "POST":

        #if symbol is not entered of if lookup fails, return error message
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("Error with stock symbol", 403)

        else:
            #saving stock info and rendering it in new html page
            stock_info = lookup(request.form.get("symbol"))
            price = stock_info["price"]
            return render_template("display.html", price = price)
    else:
        #rendering for get request
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        #checking if user field is blank
        if not request.form.get("username"):
            return apology("Must enter username", 403)

        #checking if passwords are not entered or matching
        elif not request.form.get("password") or not request.form.get("confirmation") or request.form.get("password") != request.form.get("confirmation"):
            return apology("Please re-enter password and confirmation password", 403)
        proposed_pw = request.form.get("password")
        counter = 0
        for letter in proposed_pw:
            if letter.isdigit():
                counter += 1
        if counter < 2:
            return apology("Please make sure your password has at least 2 digits")


        password = generate_password_hash(request.form.get("password"))

        #check if DB has username in it already
        result = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if result:
            return apology("Sorry, this username is already taken", 403)

        #if username is not taken, add username and hashed password into the database
        else:
            db.execute("INSERT INTO users (username, hash) VALUES ( :username, :pword)", username = request.form.get("username"), pword = password)

        #Defining row location within database so we can update the session with the appropiate user id
        rows = db.execute("SELECT * FROM users WHERE username = :username", username = request.form.get("username"))

        # Remember which user has registered
        session["user_id"] = rows[0]["id"]

        #log them into home page
        return redirect("/")


    else:
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #save user info
    user_id = session["user_id"]

    #check fields to make sure values are acceptable if the request is a POST
    if request.method == "POST":
        #check stock symbol field
        if not request.form.get("stock_symbol"):
            return apology("Please enter a stock you would like to sell")

        #check shares field for amount of shares you are looking to sell
        shares_owned = db.execute("SELECT shares FROM portfolio WHERE id = :user_id AND symbol = :symbol", user_id = user_id, symbol = request.form.get("stock_symbol"))
        shares_owned = shares_owned[0]['shares']
        if not request.form.get("shares") or shares_owned < int(request.form.get("shares")) or not shares_owned or int(request.form.get("shares")) <= 0:
            return apology("Sorry please enter a positive value or check how many shares you own")

        else:
            #assigning symbol to a var
            sym = request.form.get("stock_symbol")
            #assigning number of stocks being sold to a var
            num_sell_shares = int(request.form.get("shares"))
            #calculating new amount of shares in the portfolio for a stock
            new_shares = shares_owned - num_sell_shares

            #if user sells all of their shares, the row for this stock in the portfolio will be deleted
            if new_shares == 0:
                db.execute("DELETE FROM portfolio WHERE id = :user_id AND symbol = :symbol", user_id = user_id, symbol = sym)
            #portfolio is updated if not all shares are sold
            else:
                db.execute("UPDATE portfolio SET shares = :shares WHERE id = :user_id AND symbol = :symbol", shares = new_shares, user_id = user_id, symbol = sym)

            #setting range of variables for adding more info into history and user cash info
            stock_info = lookup(sym)
            price = (stock_info['price'])
            name = (stock_info['name'])
            total = num_sell_shares * price
            date = str(datetime.datetime.now())

            #udpate history db with line for the sell transaction
            db.execute("INSERT INTO 'history' ('id', 'type', 'symbol', 'shares', 'price', 'total', 'date_time', 'name') VALUES (:user_id, :transaction, :symbol, :shares, :price, :total, :date_time, :name)", user_id = user_id, transaction = 'sell', \
            symbol = sym.upper(), shares = num_sell_shares, price = usd(price), total = usd(total), date_time = date, name = name)

            #udpate cash amoung of user from selling these shares
            db.execute("UPDATE users SET cash = cash + :total WHERE id = :user_id", total = total, user_id = user_id)

            #pulling data for sells in
            sell_hist = db.execute("SELECT type, symbol, shares, price, total, date_time, name FROM history WHERE type = 'sell' AND id = :user_id", user_id = user_id)

            #returning a filtered history list for "bought" records
            return render_template("history.html", history = sell_hist)







    return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
