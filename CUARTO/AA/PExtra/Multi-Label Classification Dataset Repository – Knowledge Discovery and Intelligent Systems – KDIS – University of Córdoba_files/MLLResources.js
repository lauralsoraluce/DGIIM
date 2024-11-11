
function manageFormatSelect() {
   if (document.getElementById("partition").value == 'Original'){
      //Disable format select
      document.getElementById("format").setAttribute("disabled", "disabled");
   }
   else{
      //Enable format select
      document.getElementById("format").removeAttribute("disabled");
   }
}

/*
		Download any dataset
	*/
	function downloadDataset(originalName, secondName) {
		var dataPath = "http://www.uco.es/grupos/kdis/MLLResources/ucobigfiles/Datasets/"; 
		var url = dataPath;		
		var partitions = document.getElementById("partition");		
		var selectedPartition = partitions.options[partitions.selectedIndex].value;		
		var formats = document.getElementById("format");		
		var selectedFormat = formats.options[formats.selectedIndex].value;		
		if(selectedPartition == 'Original'){
			url = url + "Original/" + originalName + ".zip";
		}
		else if(selectedPartition =='FullDataset' && selectedFormat == 'Mulan'){
			url = url + "Full/" + secondName + "_Mulan.zip";
		}
		else if(selectedPartition =='FullDataset' && selectedFormat == 'Meka'){
			url = url + "Full/" + secondName + "_Meka.zip";
		}
		else if(selectedPartition =='RandTt' && selectedFormat == 'Mulan'){
			url = url + "Partitions/" + secondName + "-RandomTrainTest-Mulan.zip";
		}
		else if(selectedPartition =='RandTt' && selectedFormat == 'Meka'){
			url = url + "Partitions/" + secondName + "-RandomTrainTest-Meka.zip";
		}
		else if(selectedPartition =='StratTt' && selectedFormat == 'Mulan'){
			url = url + "Partitions/" + secondName + "-StratifiedTrainTest-Mulan.zip";
		}
		else if(selectedPartition =='StratTt' && selectedFormat == 'Meka'){
			url = url + "Partitions/" + secondName + "-StratifiedTrainTest-Meka.zip";
		}
		else if(selectedPartition =='Rand5cv' && selectedFormat == 'Mulan'){
			url = url + "Partitions/" + secondName + "-Random5FoldsCV-Mulan.zip";
		}
		else if(selectedPartition =='Rand5cv' && selectedFormat == 'Meka'){
			url = url + "Partitions/" + secondName + "-Random5FoldsCV-Meka.zip";
		}
		else if(selectedPartition =='Strat5cv' && selectedFormat == 'Mulan'){
			url = url + "Partitions/" + secondName + "-Stratified5FoldsCV-Mulan.zip";
		}
		else if(selectedPartition =='Strat5cv' && selectedFormat == 'Meka'){
			url = url + "Partitions/" + secondName + "-Stratified5FoldsCV-Meka.zip";
		}
		else if(selectedPartition =='Strat10folds' && selectedFormat == 'Mulan'){
			url = url + "Partitions/10folds/" + secondName + "-Stratified10Folds-Mulan.zip";
		}
		else if(selectedPartition =='Strat10folds' && selectedFormat == 'Meka'){
			url = url + "Partitions/10folds/" + secondName + "-Stratified10Folds-Meka.zip";
		}
		window.location=url;
	}

/*
		Download specific datasets
	*/
	document.getElementById("20NGDownload").addEventListener("click", function(){
		downloadDataset("20NG", "20NG")
	});
	document.getElementById("BibtexDownload").addEventListener("click", function(){
		downloadDataset("Bibtex", "Bibtex")
	});
	document.getElementById("BirdsDownload").addEventListener("click", function(){
		downloadDataset("Birds", "Birds")
	});
	document.getElementById("BookmarksDownload").addEventListener("click", function(){
		downloadDataset("Bookmarks", "Bookmarks")
	});
	document.getElementById("3sourcesbbc1000Download").addEventListener("click", function(){
		downloadDataset("3sources", "3sources_bbc1000")
	});
	document.getElementById("3sourcesguardian1000Download").addEventListener("click", function(){
		downloadDataset("3sources", "3sources_guardian1000")
	});
	document.getElementById("3sourcesinter3000Download").addEventListener("click", function(){
		downloadDataset("3sources", "3sources_inter3000")
	});
	document.getElementById("3sourcesreuters1000Download").addEventListener("click", function(){
		downloadDataset("3sources", "3sources_reuters1000")
	});
	document.getElementById("CAL500Download").addEventListener("click", function(){
		downloadDataset("CAL500", "CAL500")
	});
	document.getElementById("CHD49Download").addEventListener("click", function(){
		downloadDataset("CHD_49", "CHD_49")
	});
	document.getElementById("Corel16k001Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k001")
	});
	document.getElementById("Corel16k002Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k002")
	});
	document.getElementById("Corel16k003Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k003")
	});
	document.getElementById("Corel16k004Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k004")
	});
	document.getElementById("Corel16k005Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k005")
	});
	document.getElementById("Corel16k006Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k006")
	});
	document.getElementById("Corel16k007Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k007")
	});
	document.getElementById("Corel16k008Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k008")
	});
	document.getElementById("Corel16k009Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k009")
	});
	document.getElementById("Corel16k010Download").addEventListener("click", function(){
		downloadDataset("Corel16k", "Corel16k010")
	});
	document.getElementById("Corel5kDownload").addEventListener("click", function(){
		downloadDataset("Corel5k", "Corel5k")
	});
	document.getElementById("DeliciousDownload").addEventListener("click", function(){
		downloadDataset("Delicious", "Delicious")
	});
	document.getElementById("EmotionsDownload").addEventListener("click", function(){
		downloadDataset("Emotions", "Emotions")
	});
	document.getElementById("EnronDownload").addEventListener("click", function(){
		downloadDataset("Enron", "Enron")
	});
	document.getElementById("EukaryoteGODownload").addEventListener("click", function(){
		downloadDataset("EukaryoteGO", "EukaryoteGO")
	});
	document.getElementById("EukaryotePseAACDownload").addEventListener("click", function(){
		downloadDataset("EukaryotePseAAC", "EukaryotePseAAC")
	});
	document.getElementById("EurlexDCDownload").addEventListener("click", function(){
		downloadDataset("Eurlex-dc", "Eurlex-dc")
	});
	document.getElementById("EurlexEVDownload").addEventListener("click", function(){
		downloadDataset("Eurlex-ev", "Eurlex-ev")
	});
	document.getElementById("EurlexSMDownload").addEventListener("click", function(){
		downloadDataset("Eurlex-sm", "Eurlex-sm")
	});
	document.getElementById("FlagsDownload").addEventListener("click", function(){
		downloadDataset("Flags", "Flags")
	});
	document.getElementById("FoodtruckDownload").addEventListener("click", function(){
		downloadDataset("Foodtruck", "Foodtruck")
	});
	document.getElementById("GenbaseDownload").addEventListener("click", function(){
		downloadDataset("Genbase", "Genbase")
	});
	document.getElementById("GnegativeGODownload").addEventListener("click", function(){
		downloadDataset("GnegativeGO", "GnegativeGO")
	});
	document.getElementById("GnegativePseAACDownload").addEventListener("click", function(){
		downloadDataset("GnegativePseAAC", "GnegativePseAAC")
	});
	document.getElementById("GpositiveGODownload").addEventListener("click", function(){
		downloadDataset("GpositiveGO", "GpositiveGO")
	});
	document.getElementById("GpositivePseAACDownload").addEventListener("click", function(){
		downloadDataset("GpositivePseAAC", "GpositivePseAAC")
	});
	document.getElementById("HumanGODownload").addEventListener("click", function(){
		downloadDataset("HumanGO", "HumanGO")
	});
	document.getElementById("HumanPseAACDownload").addEventListener("click", function(){
		downloadDataset("HumanPseAAC", "HumanPseAAC")
	});
	document.getElementById("ImageDownload").addEventListener("click", function(){
		downloadDataset("Image", "Image")
	});
	document.getElementById("ImdbDownload").addEventListener("click", function(){
		downloadDataset("Imdb", "Imdb")
	});
	document.getElementById("LanglogDownload").addEventListener("click", function(){
		downloadDataset("Langlog", "Langlog")
	});
	document.getElementById("MediamillDownload").addEventListener("click", function(){
		downloadDataset("Mediamill", "Mediamill")
	});
	document.getElementById("MedicalDownload").addEventListener("click", function(){
		downloadDataset("Medical", "Medical")
	});
	document.getElementById("NusWideBowDownload").addEventListener("click", function(){
		downloadDataset("Nuswide_BoW", "Nuswide_BoW")
	});
	document.getElementById("NusWidecVLADplusDownload").addEventListener("click", function(){
		downloadDataset("Nuswide_cVLADplus", "Nuswide_cVLADplus")
	});
	document.getElementById("OhsumedDownload").addEventListener("click", function(){
		downloadDataset("Ohsumed", "Ohsumed")
	});
	document.getElementById("PlantGODownload").addEventListener("click", function(){
		downloadDataset("PlantGO", "PlantGO")
	});
	document.getElementById("PlantPseAACDownload").addEventListener("click", function(){
		downloadDataset("PlantPseAAC", "PlantPseAAC")
	});
	document.getElementById("rcv1subset1Download").addEventListener("click", function(){
		downloadDataset("rcv1subset1", "rcv1subset1")
	});
	document.getElementById("rcv1subset2Download").addEventListener("click", function(){
		downloadDataset("rcv1subset2", "rcv1subset2")
	});
	document.getElementById("rcv1subset3Download").addEventListener("click", function(){
		downloadDataset("rcv1subset3", "rcv1subset3")
	});
	document.getElementById("rcv1subset4Download").addEventListener("click", function(){
		downloadDataset("rcv1subset4", "rcv1subset4")
	});
	document.getElementById("rcv1subset5Download").addEventListener("click", function(){
		downloadDataset("rcv1subset5", "rcv1subset5")
	});
	document.getElementById("ReutersK500Download").addEventListener("click", function(){
		downloadDataset("Reuters-K500", "Reuters-K500")
	});
	document.getElementById("SceneDownload").addEventListener("click", function(){
		downloadDataset("Scene", "Scene")
	});
	document.getElementById("SlashdotDownload").addEventListener("click", function(){
		downloadDataset("Slashdot", "Slashdot")
	});
	document.getElementById("StackexChemistryDownload").addEventListener("click", function(){
		downloadDataset("Stackex_chemistry", "Stackex_chemistry")
	});
	document.getElementById("StackexChessDownload").addEventListener("click", function(){
		downloadDataset("Stackex_chess", "Stackex_chess")
	});
	document.getElementById("StackexCoffeeDownload").addEventListener("click", function(){
		downloadDataset("Stackex_coffee", "Stackex_coffee")
	});
	document.getElementById("StackexCookingDownload").addEventListener("click", function(){
		downloadDataset("Stackex_cooking", "Stackex_cooking")
	});
	document.getElementById("StackexCSDownload").addEventListener("click", function(){
		downloadDataset("Stackex_cs", "Stackex_cs")
	});
	document.getElementById("StackexPhilosophyDownload").addEventListener("click", function(){
		downloadDataset("Stackex_philosophy", "Stackex_philosophy")
	});
	document.getElementById("tmc2007Download").addEventListener("click", function(){
		downloadDataset("tmc2007", "tmc2007")
	});
	document.getElementById("tmc2007500Download").addEventListener("click", function(){
		downloadDataset("tmc2007-500", "tmc2007-500")
	});
	document.getElementById("VirusGODownload").addEventListener("click", function(){
		downloadDataset("VirusGO", "VirusGO")
	});
	document.getElementById("VirusPseAACDownload").addEventListener("click", function(){
		downloadDataset("VirusPseAAC", "VirusPseAAC")
	});
	document.getElementById("WaterQualityDownload").addEventListener("click", function(){
		downloadDataset("Water-quality", "Water-quality")
	});
	document.getElementById("YahooArtsDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Arts")
	});
	document.getElementById("YahooBusinessDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Business")
	});
	document.getElementById("YahooComputersDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Computers")
	});
	document.getElementById("YahooEducationDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Education")
	});
	document.getElementById("YahooEntertainmentDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Entertainment")
	});
	document.getElementById("YahooHealthDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Health")
	});
	document.getElementById("YahooRecreationDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Recreation")
	});
	document.getElementById("YahooReferenceDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Reference")
	});
	document.getElementById("YahooScienceDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Science")
	});
	document.getElementById("YahooSocialDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Social")
	});
	document.getElementById("YahooSocietyDownload").addEventListener("click", function(){
		downloadDataset("Yahoo", "Yahoo_Society")
	});
	document.getElementById("YeastDownload").addEventListener("click", function(){
		downloadDataset("Yeast", "Yeast")
	});
	document.getElementById("YelpDownload").addEventListener("click", function(){
		downloadDataset("Yelp","Yelp")
	});