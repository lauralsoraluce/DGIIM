/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;

import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author joarpe
 */
public abstract class Damage {
    private int nShields; //nWeapons;
    //private ArrayList<WeaponType> weapons;
    
    Damage (int s) {
        nShields = s;
        //nWeapons = w;
        //weapons = new ArrayList<>();
    }
    
    /*Damage (ArrayList<WeaponType> wl, int s) {
        nShields = s;
        //nWeapons = -1;
        //weapons = new ArrayList (wl);
    }*/
    
    /*Damage (Damage d) {
        nShields = d.getNShields();
        nWeapons = d.getNWeapons();
        weapons = new ArrayList(d.getWeapons());
    }*/
    
    public abstract Damage copy ();
    
    public abstract DamageToUI getUIversion ();
    
    /*private int arrayContainsType (ArrayList<Weapon> w, WeaponType t) {
        return w.indexOf(t);
    }*/
    
    public int adjustShields(ArrayList<ShieldBooster> s) {
        int nS = nShields;
        if (s.size()<nShields) 
            nS = s.size();
        
        return nS;
    }
    
    public abstract Damage adjust (ArrayList<Weapon> w, ArrayList<ShieldBooster> s); //{
        //int nS = nShields;
        //int nW = nWeapons;
        //ArrayList<WeaponType> weapon_type;
        //weapon_type = new ArrayList (weapons);
        
        //if (s.size() < nShields) 
                //nS=s.size();
        
        /*if(nWeapons!=-1) {
            if (w.size() < nWeapons)
                nW=w.size();
            return new Damage(nW, nS);
        }
        else {
            ArrayList<Weapon> weap;
            weap = new ArrayList(w);
            
            for (int i=0; i<weapons.size(); ++i) {
                boolean found = false;
                
                for (int j=0; (j<weap.size()) && !found; ++j) {
                    if (weapons.get(i)==weap.get(j).getType()) {
                        found = true;
                        weap.remove(j);
                    }
                }
                
                if (!found) {
                    weapon_type.remove(weapons.get(i));
                }
            }
            
            return new Damage(weapon_type, nS);
        }*/ 
        
        //return nS;
                
    //}
    
    public abstract void discardWeapon (Weapon w);
    
    public void discardShieldBooster () {
        if (nShields > 0) {
            nShields--;
        }
    }
    
    public boolean hasNoEffect () {
        return (nShields == 0); //&& (nWeapons == 0 || weapons.size()==0));
    }
    
    public int getNShields () {
        return nShields;
    }
    
    /*public int getNWeapons () {
        return nWeapons;
    }
    
    public ArrayList<WeaponType> getWeapons () {
        return weapons;
    }*/
    
    public String toString () {
        return ""+nShields;
    }
}