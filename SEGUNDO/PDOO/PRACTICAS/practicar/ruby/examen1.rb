require_relative 'copiaWeapon.rb'

class ExamenLazaro
	def self.run
		arma = Deepspace::Weapon.copy2("SuperArma", 3)
		puts arma.to_s
	end
end

ExamenLazaro.run
