
(define (domain dominio2)

(:requirements :strips :typing)

(:types 
    TipoUnidad TipoEdificio TipoRecurso Localizacion - Object
    Edificio Unidad - Construccion
)

(:constants
    Operador - TipoUnidad
    Extractor CentroMando CentroReclutamiento - TipoEdificio
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
    ;el edificio y necesita que tengamos el tipo de recurso x para poder ser construido
    ( necesita ?x - TipoRecurso ?y - Edificio )
    ;el recurso se tiene en general para que lo puedan usar todos los operadores, no lo tiene un operador concreto
    ( tenerRecurso ?x - TipoRecurso )
)

;la unidad u pasa de estar en x a estar en y
(:action Navegar
    :parameters (?u - Unidad ?x ?y - Localizacion)
    :precondition 
        (and 
            ;debe estar en la localización inicial
            ( en ?u ?x )

            ;el operador no puede estar extrayendo materiales porque no podría moverse
            ( not ( extrayendo ?u Mineral ) )
            ( not ( extrayendo ?u Gas ) )

            ;tiene que haber un camino entre las localizaciones de inicio y de fin
            ( camino ?x ?y )
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
    :parameters (?u - Unidad ?l - Localizacion)
    :precondition 
        (and 
            ;la unidad debe estar ya en la localización
            ( en ?u ?l )

            ;el operador no puede estar ya extrayendo materiales
            ( not ( extrayendo ?u Mineral ) )
            ( not ( extrayendo ?u Gas ) ) 

            (or
                (and 
                    ;si queremos obtener gas
                    ( asignarNodo Gas ?l )
                    ;debe existir un edificio que esté en la localización y que se de tipo extractor
                    ( exists (?edificio - Edificio) 
                        (and
                            ( en ?edificio ?l )
                            ( compTipoEdificio ?edificio Extractor )
                        )
                    )
                )
                ;si queremos obtener mineral no hay restricciones
                ( asignarNodo Mineral ?l )
            )
        )
    :effect 
        ;depende del tipo de recurso que haya en el nodo, se tiene un efecto u otro   
        (and 
            ;si el nodo es de gas, el operador extrae gas y ya se tiene ese recurso
            ( when ( asignarNodo Gas ?l ) 
                (and
                    ( extrayendo ?u Gas )
                    ( tenerRecurso Gas )
                )
            )
            ;si el nodo es de mineral, el operador extrae mineral y ya se tiene ese recurso
            ( when ( asignarNodo Mineral ?l ) 
                (and
                    ( extrayendo ?u Mineral )
                    ( tenerRecurso Mineral )
                )
            )
        )
)
;la unidad u construye el edificio concreto e en la localización l, haciendo uso del tipo de recurso r
(:action Construir
    :parameters (?u - Unidad ?e - Edificio ?l - Localizacion ?r - TipoRecurso)
    :precondition 
        (and 
            ;la unidad debe estar ya en la localización
            ( en ?u ?l )
            
            ;el operador no puede estar ocupado extrayendo materiales
            ( not ( extrayendo ?u Mineral ) )
            ( not ( extrayendo ?u Gas ) )
            
            ;necesitamos tener el recurso necesario para construir ese edificio
            ( tenerRecurso ?r ) 
            ( necesita ?r ?e )
        )
    :effect 
        (and 
            ;el edificio pasa a estar construido, y pasa a encontrarse en la localizacion dada
            ( en ?e ?l )
            ( construido ?e )
        )
)

)