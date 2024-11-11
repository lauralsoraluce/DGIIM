#encoding:utf-8

require_relative 'GameUniverseToUI.rb'
require_relative 'GameStateController.rb'
require_relative 'GameState.rb'
require_relative 'Dice.rb'
require_relative 'CardDealer.rb'
require_relative 'SpaceStation.rb'
require_relative 'Loot.rb'
require_relative 'ShotResult.rb'
require_relative 'CombatResult.rb'

module Deepspace
    class GameUniverse
        @@WIN=10

        public
        def initialize
            @dice = Dice.new
            @currentStation = nil
            @spaceStations = Array.new
            @gameState = GameStateController.new
            @turns = 0
            @currentStationIndex=-1
            @currentEnemy=nil
        end

        def combatGo(station, enemy)
            ch=@dice.firstShot

            if ch==GameCharacter::ENEMYSTARSHIP
                fire=enemy.fire
                result=station.receiveShot(fire)
                if result==ShotResult::RESIST
                    fire=station.fire
                    result=enemy.receiveShot(fire)
                    enemyWins=(result==ShotResult::RESIST)
                else
                    enemyWins=true
                end
            else
                fire=station.fire
                result=enemy.receiveShot(fire)
                enemyWins=(result==ShotResult::RESIST)
            end

            if enemyWins
                s=station.getSpeed
                moves=@dice.spaceStationMoves(s)
                if (!moves)
                    damage=enemy.damage
                    station.setPendingDamage(damage)
                    combatResult=CombatResult::ENEMYWINS
                else
                    station.move
                    combatResult=CombatResult::STATIONESCAPES
                end
            else
                aLoot=enemy.loot
                station.setLoot(aLoot)
                combatResult=CombatResult::STATIONWINS
            end
            @gameState.next(@turns, @spaceStations.size)
            combatResult
        end

        def combat
            state=state()
            if (state==GameState::BEFORECOMBAT)||(state==GameState::INIT)
                combatGo(@currentStation, @currentEnemy)
            else
                CombatResult::NOCOMBAT
            end
        end

        def discardHangar
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.discardHangar
            end
        end

        def discardShieldBooster(i)
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.discardShieldBooster(i)
            end
        end

        def discardShieldBoosterInHangar(i)
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.discardShieldBoosterInHangar(i)
            end
        end

        def discardWeapon (i)
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.discardWeapon(i)
            end
        end

        def discardWeaponInHangar (i)
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.discardWeaponInHangar(i)
            end
        end

        def state
            @gameState.state
        end

        def getUIversion
            GameUniverseToUI.new(@currentStation, @currentEnemy)
        end

        def haveAWinner
            if (@currentStation!=nil)
                return (@currentStation.nMedals >= @@WIN)
            end
        end

        def init(names)
            if(state==GameState::CANNOTPLAY)
                dealer = CardDealer.instance

                i=0
                while i<names.length
                    supplies=dealer.nextSuppliesPackage
                    station = SpaceStation.new(names.at(i), supplies)
                    @spaceStations.push(station)
                    nh=@dice.initWithNHangars
                    nw=@dice.initWithNWeapons
                    ns=@dice.initWithNShields
                    lo=Loot.new(0,nw,ns,nh,0)
                    station.setLoot(lo)
                    i=i+1
                end

                @currentStationIndex=@dice.whoStarts(names.length)
                @currentStation=@spaceStations.at(@currentStationIndex)
                @currentEnemy=dealer.nextEnemy
                @gameState.next(@turns, @spaceStations.length)
            end

        end

        def mountShieldBooster(i)
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.mountShieldBooster(i)
            end
        end

        def mountWeapon(i)
            if (state==GameState::INIT or state==GameState::AFTERCOMBAT)
                @currentStation.mountWeapon(i)
            end
        end

        def nextTurn
            if state==GameState::AFTERCOMBAT
                stationState=@currentStation.validState
                if stationState
                    @currentStationIndex=(@currentStationIndex+1)% @spaceStations.length
                    @turns=@turns+1

                    @currentStation=@spaceStations.at(@currentStationIndex)
                    @currentStation.cleanUpMountedItems
                    dealer=CardDealer.instance
                    @currentEnemy=dealer.nextEnemy
                    @gameState.next(@turns, @spaceStations.length)
                    return true
                end
                return false
            end
            return false
        end

        def to_s
            getUIversion.to_s
        end
    end
end