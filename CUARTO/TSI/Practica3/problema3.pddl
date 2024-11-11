(define (problem problema3) (:domain dominio3)
(:objects
    Operador1 Operador2 Operador3 - Unidad
    CentroMando1 Extractor1 CentroReclutamiento1 - Edificio
    LOC11 LOC12 LOC13 LOC14 LOC15 LOC21 LOC22 LOC23 LOC24 LOC31 LOC32 LOC34 LOC35 LOC42 LOC44 - Localizacion
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

    ;el Operador1 de tipo Operador está en LOC11
    ( en Operador1 LOC11 )
    ( compTipoUnidad Operador1 Operador )
    ;el Operador2 de tipo Operador está en LOC11
    ( en Operador2 LOC11 )
    ( compTipoUnidad Operador2 Operador )
    ;el Operador3 de tipo Operador está en LOC11
    ( en Operador3 LOC11 )
    ( compTipoUnidad Operador3 Operador )

    ;ponemos mineral en LOC15 Y LOC23 y gas en LOC14
    ( asignarNodo Mineral LOC15 )
    ( asignarNodo Mineral LOC23 )
    ( asignarNodo Gas LOC14 )

    ;representamos los caminos del mapa, dos casillas están conectadas en ambas direcciones, para poder moverse de una a otra y viceversa
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

)

(:goal 
    (and
        ( en CentroReclutamiento1 LOC44 )
    )
)

)
