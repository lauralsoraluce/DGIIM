/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;

import java.util.ArrayList;

/**
 *
 * @author joarpe
 */
public class Hangar {
    private int maxElements;
    private ArrayList<Weapon> weapons;
    private ArrayList<ShieldBooster> shieldBoosters;
   
    Hangar (int capacity) {
        maxElements = capacity;
        weapons = new ArrayList<>();
        shieldBoosters = new ArrayList<>();
    }
    
    Hangar (Hangar h) {
        maxElements = h.getMaxElements();
        
        weapons = new ArrayList (h.getWeapons());
        
        shieldBoosters = new ArrayList (h.getShieldBoosters());
    }
    
    HangarToUI getUIversion () {
        return (new HangarToUI(this));
    }
    
    private boolean spaceAvailable () {
        return((weapons.size() + shieldBoosters.size()) < maxElements);
    }
    
    public boolean addWeapon (Weapon w) {
        
        if (spaceAvailable()) {
            return weapons.add(w);
        }
        
        return false;
    }
            
    public boolean addShieldBoosters (ShieldBooster s) {
        if (spaceAvailable()) {
            return shieldBoosters.add(s);
        }
        return false;
    }
    
    public int getMaxElements () {
        return maxElements;
    }
    
    public ArrayList<ShieldBooster> getShieldBoosters () {
        return shieldBoosters;
    }
    
    public ArrayList<Weapon> getWeapons () {
        return weapons;
    }
    
    public ShieldBooster removeShieldBooster (int s) {
        if (shieldBoosters.size()>s && s>=0)
            return (shieldBoosters.remove(s));
        else
            return null;
    }
    
    public Weapon removeWeapon (int w) {
        if (weapons.size()>w && w>=0)
            return (weapons.remove(w));
        else
            return null;
    }
    
    public String toString () {
        return getUIversion().toString();
    }
}
