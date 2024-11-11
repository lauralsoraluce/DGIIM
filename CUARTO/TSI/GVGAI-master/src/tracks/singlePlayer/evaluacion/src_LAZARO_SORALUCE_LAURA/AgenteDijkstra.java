package tracks.singlePlayer.evaluacion.src_LAZARO_SORALUCE_LAURA;

import core.game.StateObservation;
import core.player.AbstractPlayer;
import core.game.Observation;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tracks.singlePlayer.advanced.sampleMCTS.SingleMCTSPlayer;
import tools.Vector2d;

import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.HashSet;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;


import java.util.ArrayList;
import java.util.Random;

public class AgenteDijkstra extends AbstractPlayer {
	public int num_actions;
    public Types.ACTIONS[] actions;
    protected SingleMCTSPlayer mctsPlayer;
    public Queue<Types.ACTIONS> plan;
    public boolean hayPlan;
    public ArrayList<Observation>[] muros;
    public Vector2d objetivo;
    
	public AgenteDijkstra(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		ArrayList<Types.ACTIONS> act = stateObs.getAvailableActions();
		actions = new Types.ACTIONS[act.size()];
		for (int i = 0; i < actions.length; ++i)
		{
			actions[i] = act.get(i);
		}
		num_actions = actions.length;
		
		mctsPlayer = getPlayer(stateObs, elapsedTimer);
		
		hayPlan = false;
		
		plan = new LinkedList<>();
		
		muros = stateObs.getImmovablePositions();
		
		objetivo = stateObs.getPortalsPositions(stateObs.getAvatarPosition())[0].get(0).reference;
		

	}
	
	public int distanciaManhattan(Vector2d inicio, Vector2d fin) {
	    int coste = 0;
	    coste += Math.abs(inicio.x - fin.x);
	    coste += Math.abs(inicio.y - fin.y);
	    return coste;
	}
	
	public int costeAccion(ACTIONS action) {
		return 0;
	}
    
	@Override
	/*public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		
		// Si no hay plan calculado o si los muros se han movido y hay que recalcular
		if (!hayPlan || muros!=stateObs.getImmovablePositions() )
		{	
			if (muros != stateObs.getImmovablePositions()) 
			{	
				System.out.print("HOLA");
				hayPlan=false;
				plan.clear();
				muros = stateObs.getImmovablePositions();
			}
			
			Node current_node = new Node(stateObs);
			
			// Inicialización de la cola de prioridad con el comparador adecuado
		    PriorityQueue<Node> frontier = new PriorityQueue<>(current_node.nodeComparator);

		    // Inicialización del conjunto de estados explorados
		    HashSet<Node> explored = new HashSet<>();
		    
		    boolean SolutionFound = (current_node.st.getAvatarPosition()==objetivo);
		    
		    frontier.add(current_node);
		    
		    while (!frontier.isEmpty() && !SolutionFound)
		    {
		    	frontier.poll();
		    	explored.add(current_node);
		    	if (current_node.st.getAvatarPosition()==objetivo)
		    	{
		    		SolutionFound=true;
		    	}
		    	if (!SolutionFound) {
		    		Node child_forward = new Node(current_node.st, current_node.secuencia, current_node.coste);
ç		    		//current_node.st.advance(ACTIONS.ACTION_UP);
		    		//child_forward.st = current_node.st;
		    		child_forward.st.advance(ACTIONS.ACTION_UP);
		    		if (!explored.contains(child_forward)) 
		    		{
		    			child_forward.secuencia.add(ACTIONS.ACTION_UP);
		    			child_forward.coste+=costeAccion(ACTIONS.ACTION_UP);
		    			frontier.add(child_forward);
		    		}
		    		Node child_down = current_node;
		    		//current_node.st.advance(ACTIONS.ACTION_DOWN);
		    		//child_down.st = current_node.st;
		    		child_down.st.advance(ACTIONS.ACTION_DOWN);
		    		if (!explored.contains(child_down))
		    		{
		    			child_down.secuencia.add(ACTIONS.ACTION_DOWN);
		    			child_down.coste+=costeAccion(ACTIONS.ACTION_DOWN);
		    			frontier.add(child_down);
		    		}
		    		Node child_left = current_node;
		    		//current_node.st.advance(ACTIONS.ACTION_LEFT);
		    		//child_left.st = current_node.st;
		    		child_left.st.advance(ACTIONS.ACTION_LEFT);
		    		if (!explored.contains(child_left))
		    		{
		    			child_left.secuencia.add(ACTIONS.ACTION_LEFT);
		    			child_left.coste+=costeAccion(ACTIONS.ACTION_UP);
		    			frontier.add(child_left);
		    		}
		    		Node child_right = current_node; 
		    		//current_node.st.advance(ACTIONS.ACTION_RIGHT);
		    		//child_right.st = current_node.st;
		    		child_right.st.advance(ACTIONS.ACTION_RIGHT);
		    		if (!explored.contains(child_right))
		    		{
		    			child_right.secuencia.add(ACTIONS.ACTION_RIGHT);
		    			child_right.coste+=costeAccion(ACTIONS.ACTION_RIGHT);
		    			frontier.add(child_right);
		    		}
		    	}
		    	if (!SolutionFound && !frontier.isEmpty())
		    	{
		    		current_node = frontier.poll();
		    		while (!frontier.isEmpty() && explored.contains(current_node)) {
		    			frontier.poll();
		    			if (!frontier.isEmpty())
		    			{
		    				current_node=frontier.poll();
		    			}
		    		}
		    	}
		    }
		    if (SolutionFound)
		    {
		    	plan = current_node.secuencia;
		    }
		    
			hayPlan = SolutionFound;
			
		}
		if (hayPlan) {
			if (plan.size()>0){
				return plan.poll();
			}
			else {
				System.out.println("Se completó el plan");
				hayPlan=false;
				return ACTIONS.ACTION_NIL;
			}
		}
		else {
			return ACTIONS.ACTION_NIL;
		}
		
	}*/
	
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
	    // Si no hay plan calculado o si los muros se han movido y hay que recalcular
	    if (!hayPlan || !muros.equals(stateObs.getImmovablePositions())) {
	        System.out.println("Recalculando plan...");

	        // Limpiar el plan anterior y actualizar los muros
	        plan.clear();
	        muros = stateObs.getImmovablePositions();
	        Node current_node = new Node(stateObs);

	        // Objetivo es la posición del portal más cercano al avatar
	        Vector2d objetivo = stateObs.getPortalsPositions(current_node.st.getAvatarPosition())[0].get(0).reference;

	        // Nodo inicial
	       // Node current_node = new Node(stateObs);
	        System.out.println(current_node.st.getAvatarPosition());

	        // Inicialización de la cola de prioridad con el comparador adecuado
	        PriorityQueue<Node> frontier = new PriorityQueue<>(current_node.nodeComparator);

	        // Inicialización del conjunto de nodos explorados
	        HashSet<Node> explored = new HashSet<>();

	        // Bandera para indicar si se encontró una solución
	        boolean solutionFound = (current_node.st.getAvatarPosition().equals(objetivo));

	        // Agregar el nodo inicial a la cola de prioridad
	        frontier.add(current_node);

	        // Bucle principal de búsqueda
	        while (!frontier.isEmpty() && !solutionFound) {
	            current_node = frontier.poll();
	            explored.add(current_node);

	            // Verificar si se alcanzó el objetivo
	            if (current_node.st.getAvatarPosition().equals(objetivo)) {
	                solutionFound = true;
	                break;
	            }

	            // Generar y agregar nodos hijos a la cola de prioridad
	            for (ACTIONS action : ACTIONS.values()) {
	                Node child = new Node(current_node.st.copy()); // Copiar el estado actual
	                child.st.advance(action); // Aplicar la acción al nuevo estado

	                // Verificar si el estado hijo no ha sido explorado previamente
	                if (!explored.contains(child)) {
	                    child.secuencia.add(action);
	                    child.coste += costeAccion(action);
	                    frontier.add(child);
	                }
	            }
	        }

	        // Si se encontró una solución, actualizar el plan
	        if (solutionFound) {
	            plan = current_node.secuencia;
	        }

	        // Actualizar la bandera hayPlan
	        hayPlan = solutionFound;
	    }

	    // Verificar si hay un plan disponible y devolver la siguiente acción en el plan
	    if (hayPlan) {
	        if (!plan.isEmpty()) {
	            return plan.poll();
	        } else {
	            System.out.println("Se completó el plan");
	            hayPlan = false;
	            return ACTIONS.ACTION_NIL;
	        }
	    } else {
	        return ACTIONS.ACTION_NIL;
	    }
	}

	
}

