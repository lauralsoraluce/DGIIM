#encoding:utf-8

require_relative 'EnemyToUI.rb'
require_relative 'Loot.rb'
require_relative 'Damage.rb'
require_relative 'ShotResult.rb'

module Deepspace
    class EnemyStarShip
        def initialize(n, a, s, l, d)
            @name = n
            @ammoPower = a
            @shieldPower = s
            @loot = Loot.new(l.nSupplies, l.nWeapons, l.nShields, l.nHangars, l.nMedals)
            @damage = d.copy
        end

        def self.newCopy (e)
            new(e.name, e.ammoPower, e.shieldPower, e.loot, e.damage)
        end

        def getUIversion
            EnemyToUI.new(self)
        end

        public
        def fire
            @ammoPower
        end

        def ammoPower
            @ammoPower
        end

        def damage
            @damage
        end

        def loot 
            @loot
        end

        def name 
            @name
        end

        def shieldPower 
            @shieldPower
        end

        def protection
            @shieldPower
        end

        def receiveShot (shot)
            if (protection >= shot)
                ShotResult::RESIST
            else
                ShotResult::DONOTRESIST
            end
        end

        def to_s
            getUIversion.to_s
        end
    end
end