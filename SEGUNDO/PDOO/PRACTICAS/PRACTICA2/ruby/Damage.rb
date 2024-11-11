#encoding:utf-8

require_relative 'DamageToUI.rb'
require_relative 'WeaponType.rb'

module Deepspace
    class Damage
        private_class_method :new

        def initialize(s)
            @nShields = s
        end
=begin
        def self.newNumericWeapons(w, s)
            aux = Array.new
            new(w,s,aux)
        end

        def self.newSpecificWeapons(wl, s)
            new(@@NOT_USED, s, wl)
        end

        def self.newCopy(d)
            if d.nWeapons == -1
                return newSpecificWeapons(d.weapons, d.nShields)
            else
                return newNumericWeapons(d.nWeapons, d.nShields)
            end
        end

        private
        def arrayContainsType (w, t)
            for i in(0..w.size-1) do
                if (w.at(i).type == t)
                    return i
                end
            end
            return -1
        end
=end
        def adjustShields (s)
            nS=@nShields

            if (s.size<@nShields)
                nS=s.size
            end

            return nS
        end

=begin
        def adjust (w, s)
            nW=@nWeapons
            nS=@nShields
            weapon_type=Array.new(@weapons)
            #weapons_type=WeaponType.newCopy(@weapons)

            if (s.size()<nS)
                nS=s.size()
            end
            
            if(@nWeapons!=-1)
                if (w.size < @nWeapons)
                    nW=w.size
                end
                self.class.newNumericWeapons(nW, nS)
            else
                weap=Array.new(w)
                i=0
                while i<@weapons.size
                    found = false

                    j=0
                    while j<weap.size && !found
                        if @weapons.at(i)==weap.at(j).type
                            found = true
                            weap.delete_at(j)
                        end
                        j=j+1
                    end

                    if !found
                        weapon_type.delete(@weapons.at(i))
                    end
                    i=i+1
                end
                self.class.newSpecificWeapons(weapon_type, nS)
            end
        end

        def discardWeapon (w)
            if (@nWeapons == -1)
                if (@weapons.length != 0)
                    @weapons.delete(w.type)
                end
            elsif @nWeapons >0
                @nWeapons=@nWeapons-1
            end
        end
=end

        def discardShieldBooster
            if (@nShields>0)
                @nShields = @nShields-1
            end
        end

        def hasNoEffect
            (@nShields==0)
        end

        def nShields
            @nShields
        end

=begin
        def nWeapons
            @nWeapons
        end

        def weapons
            @weapons
        end
=end

        def to_s
            ""+@nShields
        end

    end
end