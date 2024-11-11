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
public class SuppliesPackage {
    float ammoPower, fuelUnits, shieldPower;
    
    SuppliesPackage (float ammo, float fuel, float shield) {
        ammoPower = ammo;
        fuelUnits = fuel;
        shieldPower = shield;
    }
    
    SuppliesPackage (SuppliesPackage s) {
        ammoPower = s.ammoPower;
        fuelUnits = s.fuelUnits;
        shieldPower = s.shieldPower;
    }
    
    float getAmmoPower () {
        return ammoPower;
    }
    
    float getFuelUnits () {
        return fuelUnits;
    }
    
    float getShieldPower () {
        return shieldPower;
    }
    
    public String toString () {
    
        String cad = "ammoPower: " + ammoPower + "\nfuelUnits: " + fuelUnits + "\nshieldPower: " + shieldPower;
        
        return cad;
    }
}
