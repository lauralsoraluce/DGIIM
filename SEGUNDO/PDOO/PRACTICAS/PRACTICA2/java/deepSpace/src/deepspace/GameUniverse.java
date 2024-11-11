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
public class GameUniverse {
    private static final int WIN = 10;
    private int currentStationIndex, turns;
    private GameStateController gameState;
    private Dice dice;
    private SpaceStation currentStation;
    private ArrayList<SpaceStation> spaceStations;
    private EnemyStarShip currentEnemy;
    private boolean haveSpaceCity;
    
    public GameUniverse () {
        gameState = new GameStateController();
        turns = 0;
        dice = new Dice();
        spaceStations = new ArrayList<>();
    }
    
    CombatResult combat (SpaceStation station, EnemyStarShip enemy) {
        boolean enemyWins;
        GameCharacter ch=dice.firstShot();
        CombatResult combatResult;
            
        if(ch==GameCharacter.ENEMYSTARSHIPS) {
            float fire = enemy.fire();
            ShotResult result = station.receiveShot(fire);
            if(result==ShotResult.RESIST) {
                fire=station.fire();
                result=enemy.receiveShot(fire);
                enemyWins=(result==ShotResult.RESIST);
            }
            else {
                enemyWins=true;
            }
        }
        else {
            float fire = station.fire();
            ShotResult result = enemy.receiveShot(fire);
            enemyWins=(result==ShotResult.RESIST);
        }
            
        if(enemyWins) {
            float s = station.getSpeed();
            boolean moves = dice.spaceStationMoves(s);
           
            if (!moves) {
                Damage damage = enemy.getDamage();
                station.setPendingDamage(damage);
                combatResult=CombatResult.ENEMYWINS;
            }
            else {
                station.move();
                combatResult=CombatResult.STATIONESCAPES;
            }
        }
        else {
            Loot aLoot= enemy.getLoot();
            Transformation aux = station.setLoot(aLoot);
            if (aux==Transformation.GETEFFICIENT) {
                makeStationEfficient();
                combatResult=CombatResult.STATIONWINSANDCONVERTS;
            }
            else if (aux==Transformation.SPACECITY) {
                createSpaceCity();
                combatResult=CombatResult.STATIONWINSANDCONVERTS;
            }
            else
                combatResult=CombatResult.STATIONWINS;
        }
            
        gameState.next(turns, spaceStations.size());
        return combatResult;
    }
    
    public CombatResult combat () {
        GameState state=getState();
        
        if ((state==GameState.BEFORECOMBAT)||(state==GameState.INIT)) {
            return combat(currentStation, currentEnemy);
        }
        else {
            return CombatResult.NOCOMBAT;
        }    
    }
    
    public void discardHangar () {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.discardHangar();
        }
    }
    
    public void discardShieldBooster (int i) {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.discardShieldBooster(i);
        }
    }
    
    public void discardShieldBoosterInHangar (int i) {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.discardShieldBoosterInHangar(i);
        }
    }
    
    public void discardWeapon (int i) {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.discardWeapon(i);
        }
    }
    
    public void discardWeaponInHangar (int i) {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.discardWeaponInHangar(i);
        }
    }
    
    public GameState getState () {
        return gameState.getState();
    }
    
    public GameUniverseToUI getUIversion () {
        return new GameUniverseToUI (currentStation, currentEnemy);
    }
    
    public boolean haveAWinner () {
        return (currentStation.getNMedals() >= WIN);
    }
    
    public void init (ArrayList<String> names) {
        GameState state=getState();
        if (state==GameState.CANNOTPLAY) {
            CardDealer dealer = CardDealer.getInstance();
            
            for (int i=0; i<names.size(); ++i) {
                SuppliesPackage supplies = dealer.nextSuppliesPackage();
                SpaceStation station = new SpaceStation(names.get(i),supplies);
                spaceStations.add(station);
                int nh=dice.initWithHangars();
                int nw=dice.initWithWeapons();
                int ns=dice.initWithShields();
                Loot lo = new Loot(0,nw,ns,nh,0);
                station.setLoot(lo);  
            }
            
            currentStationIndex = dice.whoStarts(names.size());
            currentStation=spaceStations.get(currentStationIndex);
            
            // PRUEBA P5 EJEMPLO
            /*currentStation.setFastidia(true);*/
            
            currentEnemy=dealer.nextEnemy();
            gameState.next(turns, spaceStations.size());
        }
    }
    
    // PRUEBA P5 EJEMPLO
    /*public void fastidiar(){
        if ((getState()!=GameState.CANNOTPLAY) && currentStation.getFastidia()) {
            for (int i=0; i<spaceStations.size(); i++) {
                if (i!=currentStationIndex) {
                    if (!spaceStations.get(i).getSpaceCity())
                        spaceStations.get(i).discardHangar();
                    else
                        if (dice.fastidia())
                            spaceStations.get(i).discardHangar();
                }
            }
            currentStation.setFastidia(false);
        }
    }*/
    
    public void mountShieldBooster (int i) {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.mountShieldBooster(i);
        }
    }
    
    public void mountWeapon (int i) {
        if ((getState() == GameState.INIT) || (getState() == GameState.AFTERCOMBAT)) {
            currentStation.mountWeapon(i);
        }
    }
    
    public boolean nextTurn () {
        GameState state = getState();
        
        if(state==GameState.AFTERCOMBAT) {
            boolean stationState=currentStation.validState();
            
            if(stationState) {
                currentStationIndex=(currentStationIndex+1)%spaceStations.size();
                turns++;
                
                currentStation=spaceStations.get(currentStationIndex);
                currentStation.cleanUpMountedItems();
                CardDealer dealer = CardDealer.getInstance();
                currentEnemy = dealer.nextEnemy();
                gameState.next(turns, spaceStations.size());
                return true;
            }
            return false;
        }
        return false;
    }
    
    public String toString () {
        return getUIversion().toString();
    }
    
    private void createSpaceCity() {
        if (haveSpaceCity==false){
            ArrayList<SpaceStation> aux=new ArrayList<>();
            for (int i=0; i<spaceStations.size(); ++i) {
                if (spaceStations.get(i)!=currentStation)
                    aux.add(spaceStations.get(i));
            }
            
            currentStation=new SpaceCity(currentStation, aux);
            
            // PRUEBA P5 EJEMPLO
            //currentStation.setSpaceCity(true);
            
            haveSpaceCity=true;
            spaceStations.set(currentStationIndex, currentStation);
        }
    }
    
    private void makeStationEfficient() {
        if (dice.extraEfficiency())
            currentStation=new BetaPowerEfficientSpaceStation(currentStation);
        else
            currentStation=new PowerEfficientSpaceStation(currentStation);
        
        spaceStations.set(currentStationIndex, currentStation);
    }
    
}
