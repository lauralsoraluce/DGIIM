require_relative 'copiaWeapon.rb'

class ExamenLazaro
	def self.run
		arma = DeepSpace::Weapon.new("SuperArma", 3)
		arma.to_S
	end
end

ExamenLazaro.run
