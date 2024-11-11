
(define (domain dominio4)

(:requirements :strips :typing)

(:types 
    TipoUnidad TipoEdificio TipoRecurso Localizacion - Object
    Edificio Unidad - Construccion
)

(:constants
    Operador Androide Soldado - TipoUnidad
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

    ;lo cambiamos para que sólo se ponga una vez por tipo de edificio
    ( necesita ?x - TipoRecurso ?y - TipoEdificio )

    ;el recurso se tiene en general para que lo puedan usar todos los operadores, no lo tiene un operador concreto
    ( tenerRecurso ?x - TipoRecurso )

    ;equivalente al necesita, pero para las unidades en lugar de los edificios
    ( uniNecesita ?x - TipoRecurso ?y - TipoUnidad )

    ;en qué edificio se reclutan las distintas unidades
    ( reclutaEn ?x - TipoEdificio ?y - TipoUnidad )

    ;indica si una unidad está libre, es decir, no está extrayendo ningún material, puede moverse
    ( libre ?x - Unidad )
    ;indica si una unidad ya está "construido" o hay que tener los recursos necesarios para reclutarla en el edificio correspondiente
    ( sinReclutar ?x - Unidad)
)

;la unidad u pasa de estar en x a estar en y
(:action Navegar
    :parameters (?u - Unidad ?x ?y - Localizacion)
    :precondition 
        (and 
            ( en ?u ?x )

            ;el operador no puede estar extrayendo materiales porque no podría moverse
            (libre ?u)
            (not (sinReclutar ?u))

            ;tiene que haber un camino entre las localizaciones de inicio y de fin
            ( camino ?x ?y )
        )
    :effect 
        (and 
            ( en ?u ?y )
            ( not ( en ?u ?x ) )
        )

)
;la unidad u extrae el recurso de tipo r en la localización l
(:action Asignar
    :parameters (?u - Unidad ?l - Localizacion)
    :precondition 
        (and 
            ( en ?u ?l )
            ;sólo un operador puede extraer recursos
            (compTipoUnidad ?u Operador)

            ;el operador no puede estar ya extrayendo materiales
            (libre ?u)
            ;el operador ha de estar ya reclutado
            (not (sinReclutar ?u))

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
                ;si queremos obtener mineral
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
            (not (libre ?u))
        )
)
;la unidad u construye el edificio concreto e en la localización l, haciendo uso del tipo de recurso r
(:action Construir
    :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
    :precondition 
        (and 
            ( en ?u ?l )
            ( compTipoUnidad ?u Operador )
            (not (sinReclutar ?u))
            (not (construido ?e))

            ;no puede existir ya un edificio en esa localización
            ( not (exists ( ?edificio - Edificio )
                (and
                    ( en ?edificio ?l)
                )
            ))
            
            ;debemos tener todos los recursos que un edificio del mismo tipo del nuestro necesita para ser construido
            (forall ( ?recurso - TipoRecurso ?tipoEdificio - TipoEdificio)
                (or
                    (not 
                        (and
                            ( compTipoEdificio ?e ?tipoEdificio )
                            ( necesita ?recurso ?tipoEdificio )
                        )
                    )
                    ( tenerRecurso ?recurso )
                )
            )

            ;nuestro edificio sólo puede estar en un sitio a la vez
            ( not (exists (?pos - Localizacion)
                (and
                    ( en ?e ?pos )  
                )
            ))
            
            ;el operador no puede estar ocupado extrayendo materiales
            (libre ?u)
        )
    :effect 
        (and 
            ( en ?e ?l )
            ( construido ?e )
        )
)
;en el edificio e que está en la localización l, se va a reclutar la unidad u
(:action Reclutar
    :parameters (?e - Edificio ?u - Unidad ?l - Localizacion)
    :precondition (and 
        ;la unidad no puede estar ya reclutada, y el edificio ha de estar ya construido
        ( en ?e ?l )
        (sinReclutar ?u)
        (construido ?e)

        ;para el tipo de unidad que queremos, tenemos que estar en el tipo de edificio en el que se recluta
        (forall ( ?tiposU - TipoUnidad ?tiposE - TipoEdificio )
            (or
                (not (and
                    ( compTipoUnidad ?u ?tiposU )
                    ( compTipoEdificio ?e ?tiposE)
                ))
                ( reclutaEn ?tiposE ?tiposU )
            )
        )
        
        ;para el tipo de unidad que queremos, tenemos que disponer de todos los recursos que se necesitan para reclutarla
        (forall ( ?recurso - TipoRecurso ?tiposU - TipoUnidad)
            (or 
                (not (and 
                    ( compTipoUnidad ?u ?tiposU )
                    ( uniNecesita ?recurso ?tiposU )
                ))
                ( tenerRecurso ?recurso )
            )
        )
    )
    :effect 
    (and 
        ;la unidad pasa a estar reclutada y libre
        ( en ?u ?l )
        (not (sinReclutar ?u))
        (libre ?u)
    )
)


)