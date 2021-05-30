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
    private static Graph<String, Float> gr = new Graph<>("undirected");
    private static Graph<String, Float> minimumSpanningForest;
    
    private static void readFile(String fileName) throws GraphException {
        BufferedReader inputStream = null;
        double totalInitWeight = 0;

        System.out.println("\nOpening file...\n");
        File file = new File(fileName);
        if (!file.exists()) {
            System.out.println("File doesn't exists");
            System.exit(0);
        }
        System.out.println("Loading data from file...\n");
        try {
            inputStream = new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileName);
            System.exit(0);
        }
        try {
            // read the file line by line
            String line = inputStream.readLine();
            while (line != null) {
                String[] lineArguments = line.split(",");
                Float edgeWeight = Float.parseFloat(lineArguments[2]);
                gr.addEdge(lineArguments[0], lineArguments[1], edgeWeight);
                totalInitWeight += edgeWeight;
                line = inputStream.readLine();
            }
            inputStream.close();
            System.out.println("Data loaded.\n");
            System.out.println("At first there are " + gr.getNumberOfNodes() + " nodes and " + gr.getNumberOfEdges() + " edges. The total weight is " + totalInitWeight / 1000 + " km.\n");
        } catch (IOException e) {
            System.out.println("Impossible read the file: " + fileName);
            System.exit(0);
        }
    }

    private static void kruskal() throws GraphException, UnionFindSetException  {
        Instant start, end;
        long time;

        System.out.println("Kruskal algorithm execution...\n");
        start = Instant.now();
        minimumSpanningForest = new KruskalAlgorithm<String, Float>().kruskal(gr);
        end = Instant.now();
        System.out.println("End Kruskal algorithm execution.\n");

        time = Duration.between(start, end).toMillis();
        System.out.println("Kruskal algorithm execution time: " + time + " milliseconds.");

        System.out.println("After Kruskal algorithm execution there are " + minimumSpanningForest.getNumberOfNodes()
                + " nodes and " + minimumSpanningForest.getNumberOfEdges() + " edges. The total weight is "
                + (totalFinalWeight(minimumSpanningForest)) / 1000 + " km.\n");
    }

    private static double totalFinalWeight(Graph<String, Float> graph) throws GraphException {
        double totalWeight = 0;
        List<Edge<String, Float>> listAllEdges = graph.graphEdges();

        for (Edge<String, Float> graphEdge : listAllEdges) {
            totalWeight += graphEdge.getEdgeWeight();
        }
        return totalWeight;
    }

    public static void writeToFile(Graph<String, Float> graph) throws GraphException {
        String fileName = "minimal_italian_distance.csv";
        FileWriter outputFile = null;
        try {
            outputFile = new FileWriter(fileName);
            PrintWriter buffer = new PrintWriter(new BufferedWriter(outputFile));
            List<Edge<String, Float>> listAllEdges = graph.graphEdges();
            for (Edge<String, Float> graphEdge : listAllEdges) {
                String firstField = graphEdge.getStartNode();
                String secondField = graphEdge.getEndNode();
                String thirdField = String.valueOf(graphEdge.getEdgeWeight());
                buffer.write(firstField + "," + secondField + "," + thirdField + "\n");
            }
            buffer.close();
            outputFile.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
            System.exit(0);
        }
    }

    public static void main(String[] args) throws GraphException, UnionFindSetException {
        System.out.println("Insert the file's pathname: ");
        Scanner keyboard = new Scanner(System.in);
        String pathName = keyboard.next();
        readFile(pathName);
        kruskal();
        writeToFile(minimumSpanningForest);
        System.out.println("File with the minimal spanning forest of italian city is written.\n");
        ///home/anna/Downloads/italian_dist_graph.csv
    }
}
