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
public class Loot {
    private int nSupplies, nWeapons, nShields, nHangars, nMedals;
    private boolean getEfficient, spaceCity;
    
    Loot (int nS, int nW, int nSh, int nH, int nM) {
        nSupplies = nS;
        nWeapons = nW;
        nShields = nSh;
        nHangars = nH;
        nMedals = nM;
    }
    
    Loot (int nS, int nW, int nSh, int nH, int nM, boolean ef, boolean city) {
        nSupplies = nS;
        nWeapons = nW;
        nShields = nSh;
        nHangars = nH;
        nMedals = nM;
        getEfficient = ef;
        spaceCity = city;
    }
    
    LootToUI getUIversion () {
        return (new LootToUI(this));
    }
    
    int getNSupplies () {
        return nSupplies;
    }
    int getNWeapons () {
        return nWeapons;
    }
    int getNShields () {
        return nWeapons;
    }
    int getNHangars () {
        return nWeapons;
    }
    int getNMedals () {
        return nWeapons;
    }
    
    public boolean getEfficient() {
        return getEfficient;
    }
    
    public boolean spaceCity() {
        return spaceCity;
    }
    
    public String toString () {
        return getUIversion().toString();
    }
}
