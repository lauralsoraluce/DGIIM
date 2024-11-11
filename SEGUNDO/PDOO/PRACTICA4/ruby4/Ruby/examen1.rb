#encoding:utf-8
require_relative 'Weapon.rb'
require_relative 'WeaponType.rb'

class ExamenArcila
	def self.run
		laser = Deepspace::WeaponType::LASER
		weapon = Deepspace::Weapon.newConstructor("Pepe", 3)
		
		puts laser.to_s
		puts weapon.to_s
	end
end

ExamenArcila.run
