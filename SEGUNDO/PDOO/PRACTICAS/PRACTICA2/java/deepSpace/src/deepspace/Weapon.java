/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;

/**
 *
 * @author lauralazaro
 */
public class Weapon {
    String name;
    WeaponType type;
    int uses;
    
    Weapon(String n, WeaponType t, int u) {
        name = n;
        type = t;
        uses = u;
    }
    
    Weapon (Weapon s) {
        name = s.name;
        type = s.type;
        uses = s.uses;
    }
    
    // PRUEBA ASISTENCIA1 PRACTICA
    Weapon (String n, int u) {
        name = n;
        uses = u;
        type = new Dice().whichType();
    }
    
    WeaponToUI getUIversion () {
        return (new WeaponToUI(this));
    }
    
    WeaponType getType() {
        return type;
    }
    
    int getUses() {
        return uses;
    }
    
    float power() {
        return type.getPower();
    }
    
    float useIt() {
        if (uses > 0) {
            uses = uses-1;
            return power();
        }
        else {
            return 1.0f;
        }
    }
    
    public String toString () {
        return getUIversion().toString();
    }
}
