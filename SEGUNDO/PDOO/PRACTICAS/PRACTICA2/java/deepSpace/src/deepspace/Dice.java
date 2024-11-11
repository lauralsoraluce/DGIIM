/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;

import java.util.Random;

/**
 *
 * @author lauralazaro
 */
public class Dice {
    private final float NHANGARSPROB;
    private final float NSHIELDSPROB;
    private final float NWEAPONSPROB;
    private final float FIRSTSHOTPROB;
    private final float EXTRAEFFICIENCYPROB;
    // PRUEBA P5 EJEMPLO
    //private final float FASTIDIA;
    
    private Random generator;
    
    Dice() {
        generator = new Random();
        NHANGARSPROB = 0.25f;
        NSHIELDSPROB = 0.25f;
        NWEAPONSPROB = 0.33f;
        FIRSTSHOTPROB = 0.5f;
        EXTRAEFFICIENCYPROB = 0.8f;
        // PRUEBA P5 EJEMPLO
        // FASTIDIA=0.5f;
    }
    
    // PRUEBA ASISTENCIA1 PRACTICA
    WeaponType whichType() {
        float number = generator.nextFloat();
        
        if (number<0.5f)
            return WeaponType.LASER;
        else if (number<0.8f)
            return WeaponType.PLASMA;
        else
            return WeaponType.MISSILE;
    }
    
    int initWithHangars () {
        if (generator.nextFloat()<NHANGARSPROB) {
            return 0;
        }
        else {
            return 1;
        }
    }
    
    int initWithWeapons () {
        float aux = generator.nextFloat();
        if (aux<NWEAPONSPROB) {
            return 1;
        }
        else if (aux>=NWEAPONSPROB && aux<(2*NWEAPONSPROB)) {
            return 2;
        }
        else {
            return 3;
        }
    }
    
    int initWithShields() {
        if (generator.nextFloat()<NSHIELDSPROB) {
            return 0;
        }
        else
            return 1;
    }
    
    int whoStarts(int nPlayers) {
        return generator.nextInt(nPlayers);
    }
    
    GameCharacter firstShot () {
        if (generator.nextFloat()<FIRSTSHOTPROB)
            return GameCharacter.SPACESTATION;
        else
            return GameCharacter.ENEMYSTARSHIPS;
    }
    
    boolean spaceStationMoves (float speed) {
        return (generator.nextFloat()<speed);
    }
    
    public boolean extraEfficiency() {
        if (generator.nextFloat()<EXTRAEFFICIENCYPROB)
            return true;
        else
            return false;
    }
    
    //PRUEBA P5 PRACTICA
    /*public boolean fastidia() {
        if (generator.nextFloat()<FASTIDIA)
            return true;
        else
            return false;
    }*/
    
    public String toString () {
        int zeroHangars=0;
        int oneHangar=0;
        int oneWeapon=0;
        int twoWeapons=0;
        int threeWeapons=0;
        int numOfWeapons;
        int zeroShields=0;
        int oneShield=0;
        int firstPlayer=0;
        int secondPlayer=0;
        int spaceStation=0;
        int enemyShip=0;
        int speedUnder=0;

        for (int i=0; i<100; i++) {
            if(initWithHangars()==0)
                zeroHangars++;
            else
                oneHangar++;

            numOfWeapons = initWithWeapons();
            if(numOfWeapons==1)
                oneWeapon++;
            else if (numOfWeapons==2)
                twoWeapons++;
            else
                threeWeapons++;

            if(initWithShields()==0)
                zeroShields++;
            else
                oneShield++;

            if(whoStarts(2)==0)
                firstPlayer++;
            else
                secondPlayer++;

            if(firstShot()==GameCharacter.SPACESTATION)
                spaceStation++;
            else
                enemyShip++;

            if(spaceStationMoves(0.6f))
                speedUnder++;
        }
        
        String cad = "Zero Hangars: " + zeroHangars + "\nOne Hangar: " + 
                oneHangar + "\nOne Weapon: " + oneWeapon + "\nTwo Weapons: " + 
                twoWeapons + "\nThree Weapons: " + threeWeapons + "\nZero Shields: "
                + zeroShields + "\nOne Shield: " + oneShield + "\nFirst Player: "
                + firstPlayer + "\nSecond Player: " + secondPlayer + "\nSpace "
                + "Station: " + spaceStation + "\nEnemy Ship: " + enemyShip + 
                "\nSpeed Under: " + speedUnder + "\n";
                
        return cad;
    }
}
