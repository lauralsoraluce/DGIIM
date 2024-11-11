#encoding:utf-8

require_relative 'NumericDamageToUI.rb'
require_relative 'Damage.rb'

module Deepspace
    class NumericDamage < Damage
        public_class_method :new

        def initialize (w, s)
            super(s)
            @nWeapons=w
        end

        def copy 
            NumericDamage.new(@nWeapons, @nShields)
        end

        def getUIversion
            NumericDamageToUI.new(self)
        end

        def adjust (w, s)
            nS=adjustShields(s)
            nW=@nWeapons

            if (w.size < nW)
                nW=w.size
            end

            return NumericDamage.new(nW, nS)

        end

        def discardWeapon(w)
            if @nWeapons>0
                @nWeapons=@nWeapons-1
            end
        end

        def hasNoEffect
            return (super&&@nWeapons==0)
        end

        def nWeapons
            @nWeapons
        end

        def toString
            super + getUIversion.getWeaponInfo
        end

    end
end