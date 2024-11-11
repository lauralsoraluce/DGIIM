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
public class SpaceCity extends SpaceStation {
    SpaceStation base;
    ArrayList<SpaceStation> collaborators;
    
    public SpaceCity(SpaceStation base, ArrayList<SpaceStation> rest) {
        super(base);
        this.base = base;
        collaborators = rest;
    }
    
    public ArrayList<SpaceStation> getCollaborators() {
        return collaborators;
    }
    
    @Override public float fire() {
        float fire=0;
        //fire += base.fire();
        fire+=super.fire();
        for (int i=0; i<collaborators.size(); ++i) {
            fire+=collaborators.get(i).fire();
        }
        return fire;
    }
    
    @Override public float protection() {
        float protection=0;
        //protection+=base.protection();
        protection+=super.protection();
        for (int i=0; i<collaborators.size(); ++i) {
            protection+=collaborators.get(i).protection();
        }
        return protection;
    }
    
    @Override public Transformation setLoot(Loot loot) {
        super.setLoot(loot);
        return Transformation.NOTRANSFORM;
    }
}
