
require_relative 'SpecificDamageToUI'
require_relative 'Damage.rb'

module Deepspace
class SpecificDamage < Damage
  
  public_class_method :new
  
  attr_reader :weapons
  
  def initialize (w, s)
    super(s)

    if (w!=nil)
      @weapons=Array.new(w)
    else
      @weapons=Array.new
    end

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
  
  def copy
    return (SpecificDamage.new(@weapons, self.nShields))
  end

  def getUIversion
    return (SpecificDamageToUI.new(self))
  end

  def adjust(w, s)
    nS=adjustShields(s)

    weap_type = Array.new()
    weap = Array.new(w)

    i=0
    while i<@weapons.size
        index=arrayContainsType(weap, @weapons.at(i))
        if (index != -1)
            weap_type.push(@weapons.at(i))
            weap.delete(index)
        end

        i=i+1
    end

    return SpecificDamage.new(weap_type, nS)

  end

  def discardWeapon (w)
    if (!@weapons.empty?)
        @weapons.delete(w.type)
    end
  end

  def hasNoEffect
    return (super && @weapons.empty?)
  end

  def weapons
    @weapons
  end

  def toString
    return (super && getUIversion.getWeaponInfo)
  end
  
end # class

end # module
