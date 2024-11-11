#encoding:utf-8

require_relative 'WeaponType.rb'

module Deepspace
    class Damage
        private_class_method :new

        def initialize(s)
            @nShields = s
        end

        def adjustShields (s) 
            nS = @nShields

            if (s.size < @nShields)
                nS = s.size
            end

            return nS
        end

        def discardShieldBooster
            if (@nShields>0)
                @nShields = @nShields-1
            end
        end

        def hasNoEffect
            @nShields==0
        end

        def nShields
            @nShields
        end

        def to_s
            ""+@nShields
        end
    end
end