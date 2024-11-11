/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;

/**
 *
 * @author joarpe
 */
public class EnemyStarShip {
    private float ammoPower;
    private String name;
    private float shieldPower;
    private Loot loot;
    private Damage damage;
    
    EnemyStarShip (String n, float a, float s, Loot l, Damage d) {
        ammoPower = a;
        name = n;
        shieldPower = s;
        loot = new Loot (l.getNSupplies(), l.getNWeapons(), l.getNShields(), l.getNHangars(), l.getNMedals());
        damage = d.copy();
    }
            
    EnemyStarShip (EnemyStarShip e) {
        ammoPower = e.getAmmoPower();
        name = e.getName();
        shieldPower = e.getShieldPower();
        loot = new Loot (e.getLoot().getNSupplies(), e.getLoot().getNWeapons(), e.getLoot().getNShields(), e.getLoot().getNHangars(), e.getLoot().getNMedals());
        damage = e.getDamage().copy();
    }
    
    EnemyToUI getUIversion () {
        return (new EnemyToUI(this));
    }
    
    public float fire () {
        return ammoPower;
    }
    
    public float getAmmoPower () {
        return ammoPower;
    }
    
    public Damage getDamage () {
        return damage;
    }
    
    public Loot getLoot () {
        return loot;
    }
    
    public String getName () {
        return name;
    }
    
    public float getShieldPower () {
        return shieldPower;
    }
    
    public float protection () {
        return shieldPower;
    }
    
    public ShotResult receiveShot (float shot) {
        if (shieldPower > shot) {
            return ShotResult.RESIST;
        }
        
        else {
            return ShotResult.DONOTRESIST;
        }
    }
    
    public String toString () {
        return getUIversion().toString();
    }
}
