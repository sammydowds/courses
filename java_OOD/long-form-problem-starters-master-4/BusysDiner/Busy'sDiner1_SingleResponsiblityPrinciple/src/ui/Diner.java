package ui;

import model.Server;
import model.Chef;
import model.Order;

public class Diner {

    public static void main(String[] args) {
        Chef chef = new Chef();
        Server Server = new Server();

        for (int i=0; i < 2 ; i++) {
            System.out.println("Table " + (i + 1) + ":\n");

            Server.greet();
            Server.describeDish();
            Order o = Server.takeOrder();
            Chef.makeDish(o);

            System.out.println();

            doOrderRoutine(Server, o);
            System.out.println();
        }

        System.out.println();
        Chef.doDishes();
    }

    private static void doOrderRoutine(Server e, Order o) {
        System.out.println();
        if (o.isReadyToBeServed())
            e.deliverFood(o);
        if(o.isReadyToBePaid())
            e.takePayment(o);
    }

}
