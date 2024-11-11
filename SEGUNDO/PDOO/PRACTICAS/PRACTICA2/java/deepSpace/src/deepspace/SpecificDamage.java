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
 * @author lauralazaro
 */
public class SpecificDamage extends Damage{
    private ArrayList<WeaponType> weapons;
    
    SpecificDamage(ArrayList<WeaponType> w, int s) {
        super (s);
        
        if (w != null)
            weapons=new ArrayList(w);
        else
            weapons=new ArrayList<>();
    }
    
    @Override public SpecificDamage copy () {
        return (new SpecificDamage(weapons, this.getNShields()));
    }
    
    @Override public SpecificDamageToUI getUIversion() {
        return (new SpecificDamageToUI(this));
    }
    
    private int arrayContainsType(ArrayList<Weapon> w, WeaponType t) {
        //return w.indexOf(t);
        
        /*Iterator<Weapon> it = w.iterator();
        int i=0; 
        while (it.hasNext()){
            if (t==it.next().getType()){
                return i;
            }
            i++;
        }
        return -1;*/
        
        for (int i=0; i<w.size(); ++i) {
            if (w.get(i).getType()==t) {
                return i;
            }
        }
        return -1;
    }
    
    @Override public SpecificDamage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s) {
        int nS=adjustShields(s);
        
        ArrayList<WeaponType> weap_type = new ArrayList <>();
        ArrayList<Weapon> weap = new ArrayList (w);
            
        for (int i = 0; i < weapons.size(); ++i) {
            int index = arrayContainsType(weap, weapons.get(i));

            if (index != -1) {
                weap_type.add(weapons.get(i));
                weap.remove(index);
            }
        }
            
        return new SpecificDamage (weap_type, nS);
    }
    
    @Override public void discardWeapon(Weapon w) {
        if (!weapons.isEmpty()) {
                weapons.remove(w.getType());
        }
    }
    
    @Override public boolean hasNoEffect() {
        return (super.hasNoEffect() && weapons.isEmpty());
    }
    
    public ArrayList<WeaponType> getWeapons () {
        return weapons;
        
        /*if (weapons!=null)
            return new ArrayList<>(weapons);
        else
            return new ArrayList<>();*/
    }
    
    public String toString () {
        return (super.toString() + getUIversion().getWeaponInfo());
    }
}
