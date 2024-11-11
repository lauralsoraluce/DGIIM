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
public class SpaceStation implements SpaceFighter {
    private static final int MAXFUEL = 100;
    private static final double SHIELDLOSSPERUNITSHOT = 0.1;
    private float ammoPower;
    private float fuelUnits;
    private String name;
    private int nMedals;
    private float shieldPower;
    private Damage pendingDamage = null;
    private ArrayList<Weapon> weapons;
    private ArrayList<ShieldBooster> shieldBoosters;
    private Hangar hangar = null;
    // PRUEBA P5 EJEMPLO
    /*private boolean fastidia;
    private boolean spaceCity;*/
    
    private void assignFuelValue (float f) {
        if (f <= MAXFUEL) {
            fuelUnits = f;
        }
    }
    
    private void cleanPendingDamage () {
        if (pendingDamage.hasNoEffect()) {
            pendingDamage = null;
        }
    }
    
    SpaceStation (String n, SuppliesPackage supplies) {
        name = n;
        ammoPower = supplies.getAmmoPower();
        fuelUnits = supplies.getFuelUnits();
        shieldPower = supplies.getShieldPower();
        nMedals = 0;
        weapons = new ArrayList<>();
        shieldBoosters = new ArrayList<>();
        // PRUEBA P5 EJEMPLO
        //fastidia = false;
    }
    
    public SpaceStation(SpaceStation station) {
        name = station.getName();
        ammoPower=station.getAmmoPower();
        fuelUnits=station.getFuelUnits();
        shieldPower=station.getShieldPower();
        nMedals=station.getNMedals();
        weapons=station.getWeapons();
        shieldBoosters=station.getShieldBoosters();
        // PRUEBA P5 EJEMPLO
        //fastidia = false;
    }
    
    public void cleanUpMountedItems () {
        for (int i = 0; i < weapons.size(); ++i) {
            if (weapons.get(i).getUses() == 0) {
                weapons.remove(i);
                i--;
            }
        }
        
        for (int i = 0; i < shieldBoosters.size(); ++i) {
            if (shieldBoosters.get(i).getUses() == 0) {
                shieldBoosters.remove(i);
                i--;
            }
        }
    }
    
    public void discardHangar () {
        hangar = null;
    }
    
    public void discardShieldBooster (int i) {
        int size = shieldBoosters.size();
        
        if(i>=0 && i<size) {
            shieldBoosters.remove(i);
            
            if(pendingDamage!=null) {
                pendingDamage.discardShieldBooster();
                cleanPendingDamage();
            }
        }
    }
    
    public void discardShieldBoosterInHangar (int i) {
        if (hangar != null) {
            hangar.removeShieldBooster(i);
        }
    }
    
    public void discardWeapon (int i) {
        int size = weapons.size();
        
        if(i>=0 && i<size) {
            Weapon w = weapons.remove(i);
            
            if(pendingDamage!=null) {
                pendingDamage.discardWeapon(w);
                cleanPendingDamage();
            }
        }
    }
    
    public void discardWeaponInHangar (int i) {
        if (hangar != null) {
            hangar.removeWeapon(i);
        }
    }
    
    public float fire () {
        int size=weapons.size();
        float factor=1.0f;
        
        for (int i=0; i<size; ++i) {
            Weapon w = weapons.get(i);
            factor *= w.useIt();
        }
        
        return ammoPower*factor;
    }
    
    
    public float getAmmoPower () {
        return ammoPower;
    }
    
    public float getFuelUnits () {
        return fuelUnits;
    }
    
    public Hangar getHangar () {
        return hangar;
    }
    
    public String getName () {
        return name;
    }
    
    public int getNMedals () {
        return nMedals;
    }
    
    public Damage getPendingDamage () {
        return pendingDamage;
    }
    
    public ArrayList<ShieldBooster> getShieldBoosters () {
        return shieldBoosters;
    }
    
    public float getShieldPower () {
        return shieldPower;
    }
    
    public float getSpeed () {
        float f;
        
        f = fuelUnits / MAXFUEL;
        
        return f;
    }
    
    public SpaceStationToUI getUIversion () {
        return (new SpaceStationToUI(this));
    }
    
    public ArrayList<Weapon> getWeapons () {
        return weapons;
    }
    
    public void mountShieldBooster (int i) {     
        if (hangar != null) {
            ShieldBooster aux = hangar.removeShieldBooster(i);
            
            if (aux != null) {
                shieldBoosters.add(aux);
            }
        }
    }
    
    public void mountWeapon (int i) {
        if (hangar != null) {
            Weapon aux = hangar.removeWeapon(i);
            
            if (aux != null) {
                weapons.add(aux);
            }
        }
    }
    
    public void move () {
        fuelUnits -= getSpeed();
        
        if (fuelUnits < 0) {
            fuelUnits = 0;
        }
    }
    
    public float protection () {
        int size=shieldBoosters.size();
        float factor= 1.0f;
        
        for (int i=0; i<size; ++i) {
            ShieldBooster s = shieldBoosters.get(i);
            factor*=s.useIt();
        }
        
        return factor*shieldPower;
    }
    
    public void receiveHangar (Hangar h) {
        if (hangar == null) {
            hangar = h;
        }
    }
    
    public boolean receiveShieldBooster (ShieldBooster s) {
        if (hangar != null) {
            return hangar.addShieldBoosters(s);
        }
        return false;
    }
    
    public ShotResult receiveShot (float shot) {
        float myProtection = protection();
        
        if (myProtection>=shot) {
            shieldPower-=SHIELDLOSSPERUNITSHOT*shot;
            if (shieldPower<0.0f)
                shieldPower=0.0f;
            return ShotResult.RESIST;
        }
        else {
            shieldPower=0.0f;
            return ShotResult.DONOTRESIST;
        }
    }
    
    public void receiveSupplies (SuppliesPackage s) {
        ammoPower += s.getAmmoPower();
        shieldPower += s.getShieldPower();
        fuelUnits += s.getFuelUnits();
    }
    
    public boolean receiveWeapon (Weapon w) {
        if (hangar != null) {
            return hangar.addWeapon(w);
        }
        return false;
    }
    
    public Transformation setLoot (Loot loot) {
        CardDealer dealer = CardDealer.getInstance();
        int h=loot.getNHangars();
        if (h>0) {
            hangar = dealer.nextHangar();
            receiveHangar(hangar);
        }
        int elements = loot.getNSupplies();
        
        for (int i=0; i<elements; ++i) {
            SuppliesPackage sup = dealer.nextSuppliesPackage();
            receiveSupplies(sup);
        }
        elements = loot.getNWeapons();
        
        for (int i=0; i<elements; ++i) {
            Weapon weap = dealer.nextWeapon();
            boolean received = receiveWeapon(weap);
        }
        elements=loot.getNShields();
        
        for(int i=0; i<elements; ++i) {
            ShieldBooster sh=dealer.nextShieldBooster();
            boolean received=receiveShieldBooster(sh);
        }
        int medals = loot.getNMedals();
        
        nMedals+=medals;
        
        if (loot.getEfficient())
            return Transformation.GETEFFICIENT;
        else if (loot.spaceCity())
            return Transformation.SPACECITY;
        else
            return Transformation.NOTRANSFORM;
    }
    
    public void setPendingDamage (Damage d) {
        pendingDamage = d.adjust(weapons, shieldBoosters);
    }
    
    public boolean validState () {
        return ((pendingDamage == null) || (pendingDamage.hasNoEffect()));
    }
    
    public String toString () {
        return getUIversion().toString();
    }
    
    // PRUEBA P5 EJEMPLO
    /*public void setFastidia(boolean b) {
        fastidia = b;
    }
    public boolean getFastidia(){
        return fastidia;
    }
    public void setSpaceCity (boolean b) {
        spaceCity = b;
    }
    public boolean getSpaceCity () {
        return spaceCity;
    }*/
}
