#encoding:utf-8
require_relative 'GameCharacter.rb'

module Deepspace
	class Dice
		
		def initialize ()
			@NHANGARSPROB = 0.25
			@NSHIELDSPROB = 0.25
			@NWEAPONSPROB = 0.33
			@FIRSTSHOTPROB = 0.5
			@EXTRAEFFICIENCYPROB = 0.8
			@generator = Random.new
		end

		def extraEfficiency 
			if @generator.rand < @EXTRAEFFICIENCYPROB
				return true
			else
				return false
			end
		end
		
		def initWithNHangars ()
			if @generator.rand < @NHANGARSPROB
				return 0
			else
				return 1
			end 
		end
		
		def initWithNWeapons ()
			prob = @generator.rand
			
			if prob < @NWEAPONSPROB
				return 1
			else
				if prob < 2*@NWEAPONSPROB
					return 2
				else
					return 3
				end
			end
		end
		
		def initWithNShields ()
			if @generator.rand < @NSHIELDSPROB
				return 0
			else
				return 1
			end 
		end
		
		def whoStarts (nPlayers)
			@generator.rand(0..(nPlayers-1))
		end
		
		def firstShot ()
			if @generator.rand < @FIRSTSHOTPROB
				GameCharacter::SPACESTATION
			else
				GameCharacter::ENEMYSTARSHIP
			end
		end
		
		def spaceStationMoves (speed)
			@generator.rand < speed
		end
	end
end