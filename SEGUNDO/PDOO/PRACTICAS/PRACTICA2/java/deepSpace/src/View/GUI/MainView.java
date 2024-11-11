/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package View.GUI;

import View.DeepSpaceView;
import controller.Controller;
import deepspace.GameState;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import javax.swing.JOptionPane;

/**
 *
 * @author lauralazaro
 */
public class MainView extends javax.swing.JFrame implements DeepSpaceView {

    private static MainView instance = null;
    private String appName;
    
    private SpaceStationView station;
    private EnemyStarShipView enemy;
    
    
    public static MainView getInstance(){
        if(instance == null){
            instance = new MainView();
        }
        return instance;
    }
    
    /*public static void main(String args[]) {*/
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
    /*
        getInstance().setVisible(true);
    }*/
    
    /**
     * Creates new form MainView
     */
    private MainView() {
        initComponents();
        
        appName = "DeepSpace";
        setTitle(appName);
        
        station = new SpaceStationView();
        enemy = new EnemyStarShipView();
        
        
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e){
                Controller.getInstance().finish(0);
            }
        });
    }
    
    public String getAppName(){
        return appName;
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        exitButton = new javax.swing.JButton();
        nextTurnButton = new javax.swing.JButton();
        combatButton = new javax.swing.JButton();
        spacePanel = new javax.swing.JPanel();
        enemyPanel = new javax.swing.JPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        exitButton.setText("Exit");
        exitButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                exitButtonActionPerformed(evt);
            }
        });

        nextTurnButton.setText("Next Turn");
        nextTurnButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                nextTurnButtonActionPerformed(evt);
            }
        });

        combatButton.setText("COMBAT");
        combatButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                combatButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(spacePanel, javax.swing.GroupLayout.DEFAULT_SIZE, 762, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(35, 35, 35)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(nextTurnButton, javax.swing.GroupLayout.PREFERRED_SIZE, 160, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(combatButton, javax.swing.GroupLayout.PREFERRED_SIZE, 123, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(exitButton, javax.swing.GroupLayout.PREFERRED_SIZE, 113, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(74, 74, 74))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(enemyPanel, javax.swing.GroupLayout.PREFERRED_SIZE, 406, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(spacePanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(enemyPanel, javax.swing.GroupLayout.PREFERRED_SIZE, 401, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 108, Short.MAX_VALUE)
                        .addComponent(combatButton, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(exitButton, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(nextTurnButton, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void exitButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_exitButtonActionPerformed
        // TODO add your handling code here:
        Controller.getInstance().finish(0);
    }//GEN-LAST:event_exitButtonActionPerformed

    private void combatButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_combatButtonActionPerformed
        // TODO add your handling code here:
        Controller.getInstance().combat();
        updateView();
        revalidate();
    }//GEN-LAST:event_combatButtonActionPerformed

    private void nextTurnButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_nextTurnButtonActionPerformed
        // TODO add your handling code here:
        Controller.getInstance().nextTurn();
        updateView();
        revalidate();
    }//GEN-LAST:event_nextTurnButtonActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton combatButton;
    private javax.swing.JPanel enemyPanel;
    private javax.swing.JButton exitButton;
    private javax.swing.JButton nextTurnButton;
    private javax.swing.JPanel spacePanel;
    // End of variables declaration//GEN-END:variables

    @Override
    public void updateView() {
        
        station.setSpaceStation(Controller.getInstance().getUIversion().getCurrentStation());
        spacePanel.add(station);
        enemy.setEnemyStarShip(Controller.getInstance().getUIversion().getCurrentEnemy());
        enemyPanel.add(enemy);
        
        GameState gameState = Controller.getInstance().getState();
        
        if(gameState == GameState.INIT || gameState == GameState.BEFORECOMBAT){
            
            combatButton.setEnabled(true);
            nextTurnButton.setEnabled(false);
        }
        
        if(gameState == GameState.AFTERCOMBAT){
            
            combatButton.setEnabled(false);
            nextTurnButton.setEnabled(true);
        }
        
        // PRUEBA P5 EJEMPLO
        /*if (Controller.getInstance().getUIversion().getCurrentStation().getFastidia()) {
            fastButton.setVisible(true);
            fastButton.setEnabled(true);
        }
        else
            fastButton.setVisible(false);
        */
        revalidate();
        repaint();
        
    }

    @Override
    public void showView() {
        this.setVisible(true);
    }

    @Override
    public ArrayList<String> readNamePlayers() {
        NamesView namesView = new NamesView (this);
        
        return namesView.getNames();
    }
    
    @Override
    public boolean confirmExitMessage() {
        return (JOptionPane.showConfirmDialog(this, "¿Salir?", getAppName(), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION);
    }
    
    @Override
    public void nextTurnNotAllowedMessage() {
        JOptionPane.showMessageDialog(this, "No puedes pasar de turno. Tienes que cumplir tu castigo primero", getAppName(), JOptionPane.ERROR_MESSAGE);
    }
    
    @Override
    public void noCombatMessage() {
        JOptionPane.showMessageDialog(this, "Error: no se puede combatir", getAppName(), JOptionPane.ERROR_MESSAGE);
    }
    
    @Override
    public void lostCombatMessage() {
        JOptionPane.showMessageDialog(this, "Has perdido el combate. \nCumple tu castigo", getAppName(), JOptionPane.INFORMATION_MESSAGE);
    }

    @Override
    public void escapeMessage() {
        JOptionPane.showMessageDialog(this, "Has escapado", getAppName(), JOptionPane.INFORMATION_MESSAGE);
    }
    
    @Override
    public void wonCombatMessage() {
        JOptionPane.showMessageDialog(this, "Has ganado el combate", getAppName(), JOptionPane.INFORMATION_MESSAGE);
    }
    
    @Override
    public void wonGameMessage() {
        JOptionPane.showMessageDialog(this, "Has ganado la partida", getAppName(), JOptionPane.INFORMATION_MESSAGE);
    }
    
    @Override
    public void conversionMessage() {
        if(Controller.getInstance().getUIversion().getCurrentEnemy().getLoot().isGetEfficient()){
            JOptionPane.showMessageDialog(this, "Has ganado la partida y la estación se ha convertido en una ciudad eficiente", getAppName(), JOptionPane.INFORMATION_MESSAGE);
        }
        else{
            JOptionPane.showMessageDialog(this, "Has ganado la partida y la estación se ha convertido en una ciudad espacial", getAppName(), JOptionPane.INFORMATION_MESSAGE);
        }
    }
}
