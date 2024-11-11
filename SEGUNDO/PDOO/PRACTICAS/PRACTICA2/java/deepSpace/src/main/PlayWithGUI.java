/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import View.DeepSpaceView;
import View.GUI.MainView;
import controller.Controller;
import deepspace.GameUniverse;

/**
 *
 * @author lauralazaro
 */
public class PlayWithGUI {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        GameUniverse game = new GameUniverse();
        DeepSpaceView view = MainView.getInstance();
        Controller controller = Controller.getInstance();
        controller.setModelView(game, view);
        controller.start();
        
    }
    
}
