#encoding:utf-8

require_relative 'SpaceStation.rb'
require_relative 'Transformation.rb'
require_relative 'SuppliesPackage.rb'
require_relative 'SpaceCityToUI.rb'

module Deepspace
    class SpaceCity < SpaceStation
        attr_reader :collaborators
        def initialize(base, rest)
            super(base, SuppliesPackage.new(base.ammoPower, base.fuelUnits, base.shieldPower))
            @base=base
            @collaborators = rest
        end

        public
        def fire
            fire=0
            fire += @base.fire
            i=0
            while i<@collaborators.size
                fire+=@collaborators.at(i).fire
                i=i+1
            end
            return fire
        end 

        def protection
            protection=0
            protection+=@base.protection
            i=0
            while i<@collaborators.size
                protection+=@collaborators.at(i).protection
                i=i+1
            end
            return protection
        end

        def setLoot(loot)
            super
            return Transformation::NOTRANSFORM
        end

        def to_s
            getUIversion().to_s
          end
      
          # To UI
          def getUIversion
            return SpaceCityToUI.new(self)
          end
    end

end
