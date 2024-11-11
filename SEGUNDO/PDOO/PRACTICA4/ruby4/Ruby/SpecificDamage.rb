#encoding:utf-8

require_relative 'SpecificDamageToUI.rb'
require_relative 'Damage.rb'

module Deepspace
    class SpecificDamage < Damage
        public_class_method :new

        def initialize (wl, s)
            super(s)
            @weapons = wl
        end

        def copy
            SpecificDamage.new(@weapons, @nShields)
        end

        def getUIversion
            SpecificDamageToUI.new(self)
        end

        private
        def arrayContainsType (w, t)
            for i in(0..(w.size-1)) do
                if (w.at(i).type == t)
                    return i
                end
            end
            return -1
        end

        public
        def adjust (w, s)
            nS = adjustShields(s)

            weap_type = Array.new
            weap = Array.new(w)

            for i in (0..(@weapons.size-1)) do
                index = arrayContainsType(weap, @weapons.at(i))

                if (index != -1)
                    weap_type.push(@weapons.at(i))
                    weap.delete_at(index)
                end
            end

            SpecificDamage.new(weap_type, nS)
        end

        def discardWeapon (w)
            if (!@weapons.empty?)
                @weapons.delete(w.type)
            end
        end

        def hasNoEffect
            (super && @weapons.empty?)
        end

        def weapons
            @weapons
        end

        def to_s
            super + getUIversion.getWeaponInfo
        end
    end
end