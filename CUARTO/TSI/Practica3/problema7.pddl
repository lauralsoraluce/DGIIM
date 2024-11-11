(define (problem problema7) (:domain dominio7)
(:objects
    Operador1 Operador2 Operador3 Operador4 Androide1 Androide2 Soldado1 - Unidad
    CentroMando1 Extractor1 CentroReclutamiento1 Laboratorio1 Teletransportador1 Teletransportador2 - Edificio
    LOC11 LOC12 LOC13 LOC14 LOC15 LOC21 LOC22 LOC23 LOC24 LOC31 LOC32 LOC34 LOC35 LOC42 LOC44 - Localizacion
    InvSold1 InvTele1 - Investigacion
)

(:init
    ;el Centro de reclutamiento necesita ambos materiales
    ( necesita Mineral CentroReclutamiento )    
    ( necesita Gas CentroReclutamiento )
    ( compTipoEdificio CentroReclutamiento1 CentroReclutamiento )
    ;construimos un edificio de tipo CentroMando en LOC11
    ( construido CentroMando1 ) 
    ( en CentroMando1 LOC11 )
    ( compTipoEdificio CentroMando1 CentroMando )
    ;el edificio Extractor1 es de tipo Extractor y necesita mineral para ser construido
    ( compTipoEdificio Extractor1 Extractor )
    ( necesita Mineral Extractor )
    ;teletransportadores y laboratorio
    ( compTipoEdificio Teletransportador1 Teletransportador )
    ( compTipoEdificio Teletransportador2 Teletransportador )
    ( compTipoEdificio Laboratorio1 Laboratorio )
    ;recursos e investigaciones que necesitan para construirse
    ( necesita Mineral Laboratorio )
    ( necesita Gas Laboratorio )
    ( constNecesita Teletransportador InvTele1 )
    
    ;ponemos los dos teletransportadores ya construidos
    ( en Teletransportador1 LOC35 )
    ( en Teletransportador2 LOC32 )
    ( construido Teletransportador1 )
    ( construido Teletransportador2 )

    ;investigaciones
    ( compTipoInvestigacion InvSold1 InvestigarSoldado )
    ( compTipoInvestigacion InvTele1 InvestigarTeletransporte )
    ;recursos que necesitan las investigaciones para llevarse a cabo
    ( invNecesita Mineral InvTele1 )
    ( invNecesita Especia InvTele1 )
    ( invNecesita Mineral InvSold1 )
    ( invNecesita Gas InvSold1 )

    ;el Operador1 de tipo Operador está en LOC11, está libre y ya está reclutado
    ( en Operador1 LOC11 )
    ( compTipoUnidad Operador1 Operador )
    ( libre Operador1 )
    (not (sinReclutar Operador1))
    ;se necesita Mineral para reclutar un operador
    ( uniNecesita Mineral Operador )

    ;imponemos los tipos de las otras unidades que queremos y los materiales que necesitan, así como dónde se reclutan y las investigaciones que necesitan
    ( compTipoUnidad Operador2 Operador )
    ( compTipoUnidad Operador3 Operador )
    ( compTipoUnidad Operador4 Operador )
    ( compTipoUnidad Androide1 Androide )
    ( compTipoUnidad Androide2 Androide )
    ( compTipoUnidad Soldado1 Soldado )
    ( uniNecesita Mineral Androide )
    ( uniNecesita Mineral Soldado )
    ( uniNecesita Gas Soldado )
    ( reclutaEn CentroReclutamiento Soldado )
    ( reclutaEn CentroMando Operador )
    ( reclutaEn CentroReclutamiento Androide )
    ( sinReclutar Operador2 )
    ( sinReclutar Operador3 )
    ( sinReclutar Operador4 )
    ( sinReclutar Androide1 )
    ( sinReclutar Androide2 )
    ( sinReclutar Soldado1 )
    ( investReclutar Soldado InvSold1 )

    ;ponemos mineral en LOC15 Y LOC23 y gas en LOC14
    ( asignarNodo Mineral LOC15 )
    ( asignarNodo Mineral LOC23 )
    ( asignarNodo Gas LOC14 )
    ( asignarNodo Especia LOC13 )

    ;representamos los caminos del mapa
    ( camino LOC11 LOC12 ) ( camino LOC12 LOC11 )
    ( camino LOC11 LOC21 ) ( camino LOC21 LOC11 )
    ( camino LOC12 LOC22 ) ( camino LOC22 LOC12 )
    ( camino LOC22 LOC23 ) ( camino LOC23 LOC22 )
    ( camino LOC22 LOC32 ) ( camino LOC32 LOC22 )
    ( camino LOC32 LOC31 ) ( camino LOC31 LOC32 )
    ( camino LOC31 LOC21 ) ( camino LOC21 LOC31 )
    ( camino LOC32 LOC42 ) ( camino LOC42 LOC32 )
    ( camino LOC42 LOC44 ) ( camino LOC44 LOC42 )
    ( camino LOC23 LOC13 ) ( camino LOC13 LOC23 )
    ( camino LOC23 LOC24 ) ( camino LOC24 LOC23 )
    ( camino LOC24 LOC14 ) ( camino LOC14 LOC24 )
    ( camino LOC14 LOC15 ) ( camino LOC15 LOC14 )
    ( camino LOC24 LOC34 ) ( camino LOC34 LOC24 )
    ( camino LOC34 LOC44 ) ( camino LOC44 LOC34 )
    ( camino LOC44 LOC35 ) ( camino LOC35 LOC44 )
    ( camino LOC15 LOC35 ) ( camino LOC35 LOC15 )

    ;el número de acciones del plan empieza siendo 0 al comenzar
    (= (costePlan) 0)
)

(:goal 
    (and
        ( en CentroReclutamiento1 LOC21 )
        ( en Androide1 LOC15 )
        ( en Androide2 LOC15 )
        ( en Soldado1 LOC15 )
        ( en Laboratorio1 LOC12 )
        ;número de pasos máximo del programa, para un valor menor de este no me termina
        (< (costePlan) 35)
    )
)

)
