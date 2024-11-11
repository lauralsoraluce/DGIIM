package tracks.singlePlayer.evaluacion.src_LAZARO_SORALUCE_LAURA;

import core.game.StateObservation;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Queue;
import ontology.Types;
import java.util.LinkedList;

public class Node {
    StateObservation st;
    Queue<Types.ACTIONS> secuencia;
    int coste; 
    
    public Node(StateObservation state) {
        this.st = state.copy();
        this.secuencia = new LinkedList<>(); // Inicialización con una lista vacía
        coste = 0;
    }
    
    public Node(StateObservation st, Queue<Types.ACTIONS> secuencia) {
        this.st = st;
        this.secuencia = secuencia;
        coste = 0;
    }
    
    public Node(StateObservation st, Queue<Types.ACTIONS> secuencia, int coste) {
        this.st = st;
        this.secuencia = secuencia;
        this.coste = coste;
    }
    
    Comparator<Node> nodeComparator = new Comparator<Node>() {
        public int compare(Node n1, Node n2) {
            if (n1.st.getAvatarPosition().x <n2.st.getAvatarPosition().x || (n1.st.getAvatarPosition().x == n2.st.getAvatarPosition().x && n1.st.getAvatarPosition().y < n2.st.getAvatarPosition().y)) {
            	return -1;
            }
            else if (n1.st.getAvatarPosition().x > n2.st.getAvatarPosition().x || (n1.st.getAvatarPosition().x == n2.st.getAvatarPosition().x && n1.st.getAvatarPosition().y > n2.st.getAvatarPosition().y)) {
            	return 1;
            }
            else if (n1.coste < n2.coste)
            	return -1;
            else if (n2.coste > n2.coste)
            	return 1;
            else
            	return 0;
        }
    };
}