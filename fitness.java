import weka.core.Instances;
import weka.core.Instance;
import weka.core.SerializationHelper;
import weka.core.Utils;
import weka.core.Attribute;
import weka.core.converters.ConverterUtils.DataSource;
import weka.classifiers.Classifier;
import java.util.ArrayList;
import java.util.Enumeration;
import java.io.FileWriter;
import java.io.IOException;

public class fitness{
	public static void main(String args[]){
		try{
			String everyChromo = args[0];
			String chromo[] = everyChromo.split("/");
			String problem = args[1];
			String genes_str = args[2];
			// 0101 sphere, 4 
			int numOfGenes = Integer.parseInt(genes_str);

			String model_path = "./WEKA/SVR_WEKA-large-noiseless/smoReg-" + problem + genes_str +".model";
            FileWriter arff = new FileWriter("data.arff");

			arff.write("@relation " + problem + genes_str + "\n");
			arff.write("\n");

			for(int i=0;i<numOfGenes;i++)
			{
				arff.write("@attribute " + "f" + String.valueOf(i) + " numeric");
				arff.write("\n");
			}
			arff.write("@attribute fit numeric\n\n");
			arff.write("@data\n");
			for(int i=0;i<chromo.length;i++)
			{
				arff.write(chromo[i]);
				arff.write(",");
				arff.write("0\n");
			}
			arff.close();

			Classifier cls = (Classifier)weka.core.SerializationHelper.read(model_path);
			DataSource source = new DataSource("data.arff");
			Instances test = source.getDataSet();

			FileWriter fw = new FileWriter("result");
			for(int i=0;i<test.numInstances();i++)
			{
				double pred = cls.classifyInstance(test.instance(i));
                fw.write(new Double(pred).toString() + " ");
			}
			fw.close();

			}catch(Exception e){
				System.out.println(e);
			}
	}
}
