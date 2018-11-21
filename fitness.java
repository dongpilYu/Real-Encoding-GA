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

			String model_path = "../WEKA/SVR_WEKA-small,large (noisy)/rastrigin/smoReg-rastrigin4.model";
			FileWriter arff = new FileWriter("data.arff");

			arff.write("@relation " + problem + genes_str + "\n");
			arff.write("\n");

			for(int i=0;i<chromo[0].length();i++)
			{
				arff.write("@attribute " + "f" + String.valueOf(i) + " numeric");
				arff.write("\n");
			}
			arff.write("@attribute fit numeric\n\n");
			arff.write("@data\n");
			for(int i=0;i<chromo.length;i++)
			{
				for(int j=0;j<chromo[0].length();j++)
				{
					arff.write(chromo[i].charAt(j));
					arff.write(",");
				}
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
