
(define (domain dominio6)

(:requirements :strips :typing)

(:types 
    TipoUnidad TipoEdificio TipoRecurso TipoInvestigacion Localizacion Investigacion - Object
    Edificio Unidad - Construccion
)

(:constants
    Operador Androide Soldado - TipoUnidad
    Extractor CentroMando CentroReclutamiento Laboratorio Teletransportador - TipoEdificio
    Mineral Gas Especia - TipoRecurso
    InvestigarSoldado InvestigarTeletransporte - TipoInvestigacion

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
    ;la investigación x es de tipo y
    ( compTipoInvestigacion ?x - Investigacion ?y - TipoInvestigacion)

    ;lo cambiamos para que sólo se ponga una vez por tipo de edificio
    ( necesita ?x - TipoRecurso ?y - TipoEdificio )

    ;el recurso se tiene en general para que lo puedan usar todos los operadores, no lo tiene un operador concreto
    ( tenerRecurso ?x - TipoRecurso )

    ;equivalente al necesita, pero para las unidades en lugar de los edificios
    ( uniNecesita ?x - TipoRecurso ?y - TipoUnidad )

    ;en qué edificio se reclutan las distintas unidades
    ( reclutaEn ?x - TipoEdificio ?y - TipoUnidad )

    ;materiales necesarios para la investigacion
    ( invNecesita ?x - TipoRecurso ?y - Investigacion )

    ;investigacion que se ha hecho
    ( invTerminada ?x - Investigacion )

    ;investigaciones requeridas para reclutar unidades
    ( investReclutar ?x - TipoUnidad ?y - Investigacion )

    ;investigaciones requeridas para construir edificios
    ( constNecesita ?x - TipoEdificio ?y - Investigacion )

    ;indica si un operador está libre (equiv. a not(extrayendo ) NADA)
    ( libre ?x - Unidad )

    ;indica que una unidad concreta aún no se ha reclutado (equiv. a not(construido))
    ( sinReclutar ?x - Unidad)
)

(:functions
    (costePlan)
)

;la unidad u pasa de estar en x a estar en y
(:action Navegar
    :parameters (?u - Unidad ?x ?y - Localizacion)
    :precondition 
        (and 
            ( en ?u ?x )
            (not (sinReclutar ?u))

            ;el operador no puede estar extrayendo materiales porque no podría moverse
            ( libre ?u )

            ;tiene que haber un camino entre las localizaciones de inicio y de fin
            ( camino ?x ?y )
        )
    :effect 
        (and 
            ( en ?u ?y )
            ( not ( en ?u ?x ) )
            ;el número de acciones del plan aumenta en una unidad
            (increase (costePlan) 1)
        )

)
;la unidad u extrae el recurso de tipo r en la localización l
(:action Asignar
    :parameters (?u - Unidad ?l - Localizacion)
    :precondition 
        (and 
            ( en ?u ?l )

            ( compTipoUnidad ?u Operador )
            (not (sinReclutar ?u))

            ;el operador no puede estar ya extrayendo materiales
            ( libre ?u )

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
                ( asignarNodo Especia ?l )
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
            (when ( asignarNodo Especia ?l )
                (and
                    ( extrayendo ?u Especia )
                    ( tenerRecurso Especia )
                )
            )
            (not (libre ?u))
            (increase (costePlan) 1)
        )
)
;la unidad u construye el edificio concreto e en la localización l, haciendo uso del tipo de recurso r
(:action Construir
    :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
    :precondition 
        (and 
            ;que el operador esté en la localización concreta
            ( en ?u ?l )
            ( compTipoUnidad ?u Operador )
            (not (sinReclutar ?u))

            ;no puede existir ya un edificio en esa localización
            ( not (exists ( ?edificio - Edificio )
                (and
                    ( en ?edificio ?l)
                )
            ))

            ;el edificio no puede estar ya construiodo
            (not (construido ?e))
            
            ;debemos tener cada tipo de recurso que se necesita para construir nuestro tipo de edificio
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
            
            ;el operador no puede estar ocupado extrayendo materiales
            ( libre ?u )

            ;debemos haber acabado todas las investigaciones que se necesitan para nuestro tipo de edificio
            (forall (?tipoE - TipoEdificio ?invest - Investigacion)
                (or 
                    (not (and
                        ( compTipoEdificio ?e ?tipoE )
                        ( constNecesita ?tipoE ?invest)
                        
                    ))
                    ( invTerminada ?invest )

                )
            )
        )
    :effect 
        (and 
            ( en ?e ?l )
            ( construido ?e )
            (increase (costePlan) 1)
        )
)
;en el edificio e que está en la localización l, se va a reclutar la unidad u
(:action Reclutar
    :parameters (?e - Edificio ?u - Unidad ?l - Localizacion)
    :precondition (and 
            ( en ?e ?l )
            ;la unidad no puede estar ya reclutada
            ( sinReclutar ?u )

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
            
            ;para el tipo de unidad que queremos, tenemos que disponer de los recursos que necesitan
            (forall ( ?recurso - TipoRecurso ?tiposU - TipoUnidad)
                (or 
                    (not (and 
                        ( compTipoUnidad ?u ?tiposU )
                        ( uniNecesita ?recurso ?tiposU )
                    ))
                    ( tenerRecurso ?recurso )
                )
            )

            ;para el tipo de unidad que queremos, tenemos que tener la investigación necesaria acabada
            (forall (?invest - Investigacion ?tipoU - TipoUnidad )
                (or 
                    (not (and
                        ( compTipoUnidad ?u ?tipoU )
                        ( investReclutar ?tipoU ?invest )
                    ))
                    ( invTerminada ?invest )

                )
            )
    
        )
    :effect 
    (and 
        ( en ?u ?l )
        ;una nueva unidad empieza estando libre
        ( libre ?u )
        ;la unidad ya ha sido reclutada
        (not ( sinReclutar ?u ))
        (increase (costePlan) 1)
    )
)
;en el edificio e se completa la investigación i
(:action Investigar
    :parameters ( ?e - Edificio ?i - Investigacion)
    :precondition 
    (and 
        ;no se puede haber hecho ya la investigación
        (not (invTerminada ?i))

        
        ;tenemos que estar en un laboratorio ya construido
        ( compTipoEdificio ?e Laboratorio )
        ( construido ?e )

        ;debemos tener todos los tipos de recurso que necesita nuestra investigación
        (forall (?recurso - TipoRecurso)
            (or (not (invNecesita ?recurso ?i))
                (tenerRecurso ?recurso)
            )
        )
    )
    :effect 
    (and 
        (invTerminada ?i)
        (increase (costePlan) 1)
    )
)



)