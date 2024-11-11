#encoding:utf-8

require_relative 'HangarToUI.rb'

module Deepspace
    class Hangar
        attr_writer :shieldBoosters, :weapons
        def initialize (capacity)
            @maxElements = capacity
            @shieldBoosters = Array.new
            @weapons = Array.new
        end

        def self.newCopy(h)
            aux=new(h.maxElements)
            aux.shieldBoosters=h.shieldBoosters
            aux.weapons=h.weapons

            return aux
        end

        def getUIversion
            HangarToUI.new(self)
        end

        private
        def spaceAvailable
            (@shieldBoosters.size + @weapons.size)<maxElements
        end

        public
        def addWeapon (w)
            if (spaceAvailable)
                @weapons.push(w)
                return true
            elsif
                false
            end
        end

        def addShieldBooster(s)
            if (spaceAvailable)
                @shieldBoosters.push(s)
                return true
            elsif
                false
            end
        end

        def maxElements
            @maxElements
        end

        def shieldBoosters
            @shieldBoosters
        end

        def weapons
            @weapons
        end

        def removeShieldBoosters (s)
            if (s>=0 && s<@shieldBoosters.size)
                return @shieldBoosters.delete_at(s)
            else
                nil
            end
        end

        def removeWeapons (w)
            if (w>=0 && w<@weapons.size)
                return @weapons.delete_at(w)
            else
                nil
            end
        end

        def to_s
            getUIversion.to_s
        end

    end
end
