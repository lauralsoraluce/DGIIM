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
public class ShieldBooster {
    String name;
    float boost;
    int uses;
    
    ShieldBooster(String n, float b, int u) {
        name = n;
        boost = b;
        uses = u;
    }
    
    ShieldBooster (ShieldBooster s) {
        name = s.name;
        boost = s.boost;
        uses = s.uses;
    }
    
    ShieldToUI getUIversion () {
        return (new ShieldToUI(this));
    }
    
    float getBoost () {
        return boost;
    }
    
    int getUses () {
        return uses;
    }
    
    float useIt () {
        if (uses>0) {
            uses = uses-1;
            return boost;
        }
        else {
            return 1.0f;
        }
    }
    
    public String toString () {
        return getUIversion().toString();
    }
}
