package graphs;

/* import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.IOException;
*/

import java.util.*;
import java.io.*;
import java.nio.*;
import java.time.Instant;
import java.time.Duration;
import unionfindset.UnionFindSetException;

// minimumSpanningForest = foresta minima ricoprente

public class GraphKruskalMain { 
    private static Instant start, end;
    private static void readFile(String fileName) throws GraphException, UnionFindSetException {
        try{
            Graph<String,Float> gr = new Graph<>("undirected");
            Graph<String,Float> minimumSpanningForest;
            double totalInitWeight = 0;

            System.out.println("\nOpening file...\n");
            File file = new File(fileName);
            if (!file.exists()){
                System.out.println("File doesn't exists");
                System.exit(0);
            }

            System.out.println("Loading data from file...\n");
            BufferedReader inputStream = new BufferedReader(new FileReader(file));
            // read the file line by line
            String line = inputStream.readLine();
            while (line != null) {
                String lineArguments[] = line.split(",");
                Float edgeWeight = Float.parseFloat(lineArguments[2]);
                gr.addEdge(lineArguments[0], lineArguments[1], edgeWeight);
                totalInitWeight += edgeWeight;
                line = inputStream.readLine();
            }
            System.out.println("Data loaded.\n");
            System.out.println("At first there are " + gr.getNumberOfNodes() + " nodes and " + gr.getNumberOfEdges() + " edges. The total weight is " + totalInitWeight/1000 + " km.\n");
            
            System.out.println("Kruskal algorithm execution...\n");
            start = Instant.now();
            minimumSpanningForest = new KruskalAlgorithm<String,Float>().kruskalAlgorithm(gr);
            end = Instant.now();
            System.out.println("End Kruskal algorithm execution.\n");
            System.out.println("After Kruskal algorithm execution there are " + minimumSpanningForest.getNumberOfNodes() + " nodes and " + minimumSpanningForest.getNumberOfEdges() + " edges. The total weight is " + (totalFinalWeight(minimumSpanningForest))/1000 + " km.\n");
            
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileName);
        } catch (IOException e) {
            System.out.println("Impossible read the file: " + fileName);
        }
    }

    private static double totalFinalWeight(Graph<String, Float> graph) throws GraphException{
        double totalWeight = 0;
        List<Edge<String,Float>> listEdges = graph.graphEdges();

        for(Edge<String,Float> graphEdge : listEdges){
			totalWeight += graphEdge.getEdgeWeight();
		}
        return totalWeight;
    }

    public static void main(String[] args) throws GraphException, UnionFindSetException {
        System.out.println("Insert the file's pathname: ");
        Scanner keyboard = new Scanner(System.in);
        String pathName = keyboard.next();
        readFile(pathName);
        ///home/anna/Downloads/italian_dist_graph.csv
        long time = Duration.between(start, end).toMillis();
        System.out.println("Kruskal algorithm execution time: " + time + " milliseconds.");
    }
}
