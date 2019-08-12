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
import java.nio.charset.Charset;
import org.apache.commons.math3.complex.Complex;
import org.apache.commons.math3.transform.DftNormalization;
import org.apache.commons.math3.transform.FastFourierTransformer;
import org.apache.commons.math3.transform.TransformType;
/*
    0101/1011/0000/1111 nk 4 형태의 입력

    String chromo[], problem, problem_size
*/
public class fitness{

    List<String> walsh_chromos = new ArrayList<String>();
    List<String> fourier_chromos = new ArrayList<String>();

    static int binomialCoeff(int n, int k){
        int c[][] = new int[n+1][k+1];

        for(int i=0;i<=n;i++) {
            for(int j=0;j<=min(i,k);j++) {
                if(j==0 || j==i)
                    c[i][j] = 1;
                else
                    c[i][j] = c[i-1][j-1] + c[i-1][j];
            }
        }
        return c[n][k];
    }
    static int calc_walsh(ArrayList<Integer> numbers, int k){

        int pos = 0;
        int exp = 0;
        ArrayList<Integer> binary = new ArrayList<Integer>();
        while(true){

            binary.add(k%2);
            k = (int)k/2;
            pos += 1;
            if(k==0)
                break;

        }

        for(int i=pos-1;i>-1;i--)
            exp += (numbers.get(i)*binary.get(i));
        if(exp % 2 == 0)
            return 1;
        else
            return -1;
    }
    public void walsh_transform(String[] chromo){
        /*
            기존의 walsh_transform ArrayList<Integer> numbers는 염색체 하나를 저장
            String[] chromo는 한 세대의 모든 염색체를 가진 문자열

            [0101010, 10101111, .... , 11111111]
        */
        ArrayList<Integer> numbers = new ArrayList<Integer>();

        for(int i=0;i<chromo.length;i++){

            for(int j=0;j<chromo[i].length;j++){
                numbers[j] = chromo[i][j];
            }
            int num_coeff0 = 1;
            int num_coeff1 = n;
            int num_coeff2 = binomialCoeff(n, 2);
            int num_coeff3 = binomialCoeff(n, 3);
            int[] walsh_coeff = new int[num_coeff0 + num_coeff1 + num_coeff2 + num_coeff3];
            int[] order_one = new int[num_coeff1];
            int[] order_two = new int[num_coeff2];
            int[] order_three = new int[num_coeff3];
            for (int i = 0; i < n; i++)
                order_one[i] = (int) Math.pow(2, i);
            int idx = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    order_two[idx] = order_one[i] + order_one[j];
                    idx++;
                }
            }
            idx=0;
            for(int i=0;i<n;i++) {
                for(int j=i+1;j<n;j++){
                    for(int k=j+1;k<n;k++){
                        order_three[idx] = order_one[i]+order_one[j]+order_one[k];
                        idx++;
                    }
                }
            }

            if(walsh_order<=2)
                num_coeff3=0;
            if(walsh_order<=1)
                num_coeff2=0;

            idx=0;
            walsh_coeff[idx++] = calc_walsh(numbers,0);
            for(int i=0;i<num_coeff1;i++)
                walsh_coeff[idx++] = calc_walsh(numbers, order_one[i]);
            for(int i=0;i<num_coeff2;i++)
                walsh_coeff[idx++] = calc_walsh(numbers, order_two[i]);
            for(int i=0;i<num_coeff3;i++)
                walsh_coeff[idx++] = calc_walsh(numbers, order_three[i]);

            String walshStr = Arrays.toString(walsh_coeff)
            walsh_chromos.add(walshStr);
            // walsh_coeff -> String화해서 전달 리스트에 삽입
        }
    }
    public void fourier_transform(String[] chromo){

        // [-1.32,4-23,-2.31 , 3.12,4.12,-3.41 , ...]
        ArrayList<Double> numbers = new ArrayList<Double>();
        for(int i=0;i<chromo.length;i++){ // number of population

            String[] genes = chromo[i].split(","); // number of genes = problem size
            for(int j=0;j<genes.length;j++)
                numbers[j] = Double.parseDouble(genes[j]);

            FastFourierTransformer transformer = new FastFourierTransformer(DftNormalization.STANDARD);
            Complex[] signature = transformer.transform(numbers, TransformType.FORWARD);

            String geneStr = "";

            for(int j=0;j<signature.length;j++)
            {
                String gene = Double.toString(signature[j].getReal());
                geneStr = genes.concat(gene);
            }
            fourier_chromos.add(geneStr)
        }
    }
	public static void main(String args[]){
		try{
			String everyChromo = args[0];
			String chromo[] = everyChromo.split("/");
			String problem = args[1];
			String genes_str = args[2];
			String transform = args[3];
            String model = args[4];
            // 0101/0111, sphere, 4, fourier[walsh, normal], svr
			int numOfGenes = Integer.parseInt(genes_str);

			String model_path = "C:\\Users\\dong\\Desktop\\hindawi\\data\\" + problem + "_" + transform + "\\" + model + "_" + transform + "_model\\" + transform + "_" + problem + genes_str +".model";
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

            fourier_transform(chromo);
            walsh_transform(chromo);
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
