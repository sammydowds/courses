package model;

import java.util.List;

/**
 * The control class for the systems in a theatre
 */

public class Theatre {

    private List<StageLight> stageLights;
    private List<HouseLight> houseLights;
    private Curtain curtain;

    private int showTime; // hour that the show begins

    private static final int SCENE_I = 1;

    public Theatre(int showTime, List<StageLight> stageLights, List<HouseLight> houseLights, Curtain curtain) {
        this.showTime = showTime;
        this.stageLights = stageLights;
        this.houseLights = houseLights;
        this.curtain = curtain;
    }


    /**
     * MODIFIES: this
     * EFFECTS: Close the curtain, turn off all the stage lights, and turn on all the house lights.
     */
    public void openHouse() {
        // TODO complete this method
        //close the curtain
        curtain.close();

        //for each stage light, turn it off
        for (Integer light : stageLights) {
          light.turnOff();
        }

        //for each house light, turn it on
        for (Integer light: houseLights) {
          light.turnOn();
        }

    }

    /**
     * REQUIRES: currTime is a positive integer between 1 and 12
     * MODIFIES: this
     * EFFECTS: If it is time to start the show, then close the curtain, turn off the house lights,
     * turn on the stage lights that are part of Scene 1, and finally, open the curtain. Return true
     * if the show was started, otherwise false.
     */

    public boolean startShow(int currTime) {
        // TODO complete this method
        if ( isTimeToStartShow() ) {
          //turning off house lights
          for (Integer light: houseLights) {
            light.turnOff();
          }
          //checking if stage light is part of scene, if so turn it on
          for (Integer light: stageLights) {
            if (light.isPartOfScene(SCENE_I)) {
              light.turnOn();
            }
          }
          //setting curtain to open
          curtain.open()

          //ready for the show!
          return true;
        }
        return false;
    }

    /**
     * EFFECTS: return true if the current time is greater than or equal to the show start time
     */
    private boolean isTimeToStartShow(int currTime) {
        return currTime >= showTime;
    }


}
