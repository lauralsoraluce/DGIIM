
(define (domain dominio1)

(:requirements :strips :typing)

(:types 
    TipoUnidad TipoEdificio TipoRecurso Localizacion - Object
    Edificio Unidad - Construccion
)

(:constants
    Operador - TipoUnidad
    CentroMando CentroReclutamiento - TipoEdificio
    Mineral Gas - TipoRecurso
)

(:predicates 
    ;un edificio o unidad x está localizado en y
    ( en ?x - Construccion ?y - Localizacion )
    ;un edificio x ha sido construido
    ( construido ?x - Edificio )
    ;las localizaciones x e y están conectadas, se puede ir de una a otra directamente
    ( camino ?x ?y - Localizacion )
    ;en la localización y hay recurso de tipo x
    ( asignarNodo ?x - TipoRecurso ?y - Localizacion )
    ;la unidad x está extrayendo el tipo de recurso y => no debe poder moverse de la localización en la que está
    ( extrayendo ?x - Unidad ?y - TipoRecurso ) 
    ;la unidad x es del tipo y
    ( compTipoUnidad ?x - Unidad ?y - TipoUnidad )
    ;el edificio x es del tipo y
    ( compTipoEdificio ?x - Edificio ?y - TipoEdificio )
)

;la unidad u pasa de estar en x a estar en y
(:action Navegar
    :parameters (?u - Unidad ?x ?y - Localizacion)
    :precondition 
        (and 
            ;debe estar en la localización inicial
            ( en ?u ?x )
            ;no puede estar extrayendo ningún material porque no podría moverse en ese caso
            ( not ( extrayendo ?u Mineral ) )
            ( not ( extrayendo ?u Gas ) )
            ;las dos localizaciones han de estar directamente conectadas
            ( camino ?x ?y )
            ;para que una unidad se mueva de una casilla a otra cuando estas no están directamente conectadas, 
            ;se llamará a la acción Navegar tantas veces como haga falta pasando siempre a una casilla adyacente a en la que está
        )
    :effect 
        (and 
            ;la unidad pasa a estar en la nueva localización y ya no está en la anterior para evitar que figure en dos localizaciones a la vez
            ( en ?u ?y )
            ( not ( en ?u ?x ) )
        )

)
;la unidad u extrae el recurso de tipo r en la localización l
(:action Asignar
    :parameters (?u - Unidad ?l - Localizacion ?r - TipoRecurso)
    :precondition 
        (and 
            ;la unidad debe estar ya en la localización
            ( en ?u ?l )
            ;no puede estar extrayendo ya
            ( not ( extrayendo ?u Mineral ) )
            ( not ( extrayendo ?u Gas ) ) 
            ;en la localizacion debe existir el recurso que queremos extraer
            ( asignarNodo ?r ?l )
        )
    :effect    
        (and 
            ;la unidad extrae el recurso => no debe poder moverse de esta localización
            ( extrayendo ?u ?r )
        )
)
)