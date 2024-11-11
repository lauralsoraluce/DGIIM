/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;

import java.util.ArrayList;

/**
 *
 * @author lauralazaro
 */
public class NumericDamage extends Damage {
    private int nWeapons;
    
    NumericDamage (int w, int s) {
        super(s);
        nWeapons=w;
    }
    
    @Override public NumericDamage copy() {
        return (new NumericDamage(nWeapons, this.getNShields()));
    }
    
    @Override public NumericDamageToUI getUIversion() {
        return (new NumericDamageToUI(this));
    }
    
    @Override public NumericDamage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s) {
        int nS=adjustShields(s);
        int nW=nWeapons;
        
        if (w.size()<nWeapons)
            nW=w.size();
        
        return new NumericDamage(nW, nS);
    }
    
    @Override public void discardWeapon(Weapon w) {
        if (nWeapons>0)
            nWeapons--;
    }
    
    @Override public boolean hasNoEffect () {
        return (super.hasNoEffect() && nWeapons==0); 
    }
    
    public int getNWeapons () {
        return nWeapons;
    }
    
    @Override public String toString () {
        return (super.toString() + getUIversion().getWeaponInfo());
    }
}
