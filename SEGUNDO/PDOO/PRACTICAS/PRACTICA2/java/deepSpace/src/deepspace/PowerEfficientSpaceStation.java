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
public class PowerEfficientSpaceStation extends SpaceStation {
    private final float EFFICIENCYFACTOR =1.10f;
    
    PowerEfficientSpaceStation(SpaceStation station) {
        super(station);
    }
    
    @Override public float fire() {
        return super.fire()*EFFICIENCYFACTOR;
    }
    
    @Override public float protection() {
        return super.protection()*EFFICIENCYFACTOR;
    }
    
    @Override public Transformation setLoot(Loot loot) {
        Transformation check = super.setLoot(loot);
        
        if (check==Transformation.SPACECITY)
            return Transformation.NOTRANSFORM;
        else
            return check;
    }
    
}
