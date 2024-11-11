#encoding:utf-8

require 'singleton'

require_relative 'SpaceStationToUI.rb'
require_relative 'ShotResult.rb'
require_relative 'CardDealer.rb'
require_relative 'SuppliesPackage.rb'
require_relative 'Hangar.rb'
require_relative 'Transformation.rb'

module Deepspace
    class SpaceStation 
        @@MAXFUEL = 100
        @@SHIELDLOSSPERUNITSHOT = 0.1

        private
        def assignFuelValue (f)
            if (f<=@@MAXFUEL)
                @fuelUnits = f 
            else
                @fuelUnits = @@MAXFUEL
            end
        end

        def cleanPendingDamage
            if (@pendingDamage != nil)
                if (@pendingDamage.hasNoEffect)
                    @pendingDamage = nil
                end
            end
        end

        public 
        def initialize (n, supplies)
            @name = n
            @ammoPower=0
            @fuelUnits=0
            @shieldPower=0
            receiveSupplies(supplies)
            @weapons = Array.new
            @shieldBoosters=Array.new
            @hangar = nil
            @pendingDamage= nil
            @nMedals = 0
        end

        def self.newCopy (station)
            aux = new(station.name, SuppliesPackage.new(station.ammoPower, station.fuelUnits, station.shieldPower))
            aux.nMedals = station.nMedals
            aux.weapons = Array.new(station.weapons)
            aux.shieldBoosters = Array.new(station.shieldBoosters)

            if (station.pendingDamage != nil)
                aux.pendingDamage = station.pendingDamage.copy
            end

            if (station.hangar != nil)
                aux.hangar = Hangar.newCopy(station.hangar)
            end

            return aux
        end

        def cleanUpMountedItems
            for i in(0..(@weapons.size-1)) do
                if (@weapons.at(i).uses==0)
                    @weapons.delete_at(i)
                    i=i-1
                end
            end

            for i in(0..(@shieldBoosters.size-1)) do
                if (@shieldBoosters.at(i).uses==0)
                    @shieldBoosters.delete_at(i)
                    i=i-1
                end
            end
        end

        def discardHangar
            @hangar = nil
        end

        def discardShieldBooster(i)
            size = @shieldBoosters.size()

            if ((i >= 0) && (i < size))
                @shieldBoosters.delete_at(i)

                if (@pendingDamage != nil)
                    @pendingDamage.discardShieldBooster
                    cleanPendingDamage()
                end
            end
        end

        def discardShieldBoosterInHangar(i)
            if (@hangar!=nil)
                @hangar.removeShieldBoosters(i)
            end
        end

        def discardWeapon(i)
            size = @weapons.size()

            if ((i >= 0) && (i < size))
                w = @weapons.delete_at(i)

                if (@pendingDamage != nil)
                    @pendingDamage.discardWeapon(w)
                    cleanPendingDamage()
                end
            end
        end

        def discardWeaponInHangar(i)
            if (@hangar != nil)
                @hangar.removeWeapons(i)
            end
        end

        def fire
            size = @weapons.size()
            factor = 1.0

            i = 0
            while (i < size)
                w = @weapons.at(i)
                factor = factor * w.useIt()
            
                i = i+1
            end

            return (@ammoPower*factor)
        end

        def ammoPower
            @ammoPower
        end

        def fuelUnits
            @fuelUnits
        end

        def hangar
            @hangar
        end

        def name
            @name
        end

        def nMedals
            @nMedals
        end

        def pendingDamage
            @pendingDamage
        end

        def shieldBoosters
            @shieldBoosters
        end

        def shieldPower
            @shieldPower
        end

        def getSpeed 
            @fuelUnits.to_f/@@MAXFUEL
        end

        def getUIversion
            SpaceStationToUI.new(self)
        end

        def weapons
            @weapons
        end

        def mountShieldBooster (i)
            if (@hangar!=nil)
                aux = @hangar.removeShieldBoosters(i)

                if (aux != nil) 
                    @shieldBoosters.push(aux)
                end
            end
        end

        def mountWeapon(i)
            if (@hangar!=nil)
                aux = @hangar.removeWeapons(i)
                
                if (aux != nil)
                    @weapons.push(aux)
                end
            end
        end

        def move
            @fuelUnits = @fuelUnits - getSpeed
            if (@fuelUnits<0)
                @fuelUnits=0
            end
        end

        def protection 
            size = @shieldBoosters.size()
            factor = 1.0

            i = 0
            while (i < size)
                s = @shieldBoosters.at(i)
                factor = factor * s.useIt()
            
                i = i+1
            end

            return (@shieldPower * factor)
        end

        def receiveHangar(h)
            if (@hangar == nil)
                @hangar=h 
            end
        end

        def receiveShieldBooster(s)
            if (@hangar!=nil)
                @hangar.addShieldBooster(s)
            else
                return false
            end
        end

        def receiveShot(shot)
            myProtection = protection()

            if (myProtection >= shot)
                @shieldPower = @shieldPower - (@@SHIELDLOSSPERUNITSHOT * shot)

                if (0.0 > @shieldPower)
                    @shieldPower = 0.0
                end

                return ShotResult::RESIST
            else
                @shieldPower = 0.0

                return ShotResult::DONOTRESIST
            end
        end

        def receiveSupplies (s)
            assignFuelValue(@fuelUnits + s.fuelUnits)
            @ammoPower = @ammoPower + s.ammoPower
            @shieldPower = @shieldPower + s.shieldPower
        end

        def receiveWeapon (w)
            if (@hangar!=nil)
                @hangar.addWeapon(w)
            else
                return false
            end
        end

        def setLoot (loot)
            dealer = CardDealer.instance()
            h = loot.nHangars()

            if (h > 0)
                @hangar = dealer.nextHangar()
                receiveHangar(@hangar)
            end

            elements = loot.nSupplies()

            i = 0
            while (i < elements)
                sup = dealer.nextSuppliesPackage()
                receiveSupplies(sup)
                
                i = i+1
            end

            elements = loot.nWeapons()

            i = 0
            while (i < elements)
                weap = dealer.nextWeapon()
                receiveWeapon(weap)
                
                i = i+1
            end

            elements = loot.nShields()

            i = 0
            while (i < elements)
                sh = dealer.nextShieldBooster()
                receiveShieldBooster(sh)
                
                i = i+1
            end

            medals = loot.nMedals()

            @nMedals = @nMedals + medals

            if (loot.efficient)
                return Transformation::GETEFFICIENT
            else
                if (loot.spaceCity)
                    return Transformation::SPACECITY
                else
                    return Transformation::NOTRANSFORM
                end
            end
        end

        def setPendingDamage(d)
            if (d != nil)
                @pendingDamage=d.adjust(@weapons, @shieldBoosters)
            end
        end

        def validState
            if (@pendingDamage==nil) 
                return true
            else 
                return @pendingDamage.hasNoEffect
            end
        end

        def to_s
            getUIversion.to_s
        end

    end
end
