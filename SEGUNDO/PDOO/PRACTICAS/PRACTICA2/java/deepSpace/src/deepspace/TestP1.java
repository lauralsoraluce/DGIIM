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
public class TestP1 {
    static int main() {
        Dice gameDice = new Dice();
        
        System.out.print("\n---------------------------------------\n");
        
        Loot gameLoot = new Loot(1,1,1,1,1);
        System.out.print("Clase Loot:\n\n" + gameLoot.toString());
        
        System.out.print("\n---------------------------------------\n");
        
        ShieldBooster firstShield = new ShieldBooster("shield", 3, 5);
        System.out.print("Clase ShieldBooster:\n\n" + firstShield.toString());
        
        System.out.print("\n---------------------------------------\n");
        
        SuppliesPackage supplies = new SuppliesPackage(3, 7, 2.5f);
        System.out.print("Clase SuppliesPackage:\n\n" + supplies.toString());
        
        System.out.print("\n---------------------------------------\n");
        
        Weapon gameweapon = new Weapon("Sniper", WeaponType.MISSILE, 3);
        System.out.print("Clase Weapon:\n\n" + gameweapon.toString());
        
        System.out.print("\n---------------------------------------\nClase Dice:\n\n" + gameDice.toString());
        
        return 0;
    }
}
