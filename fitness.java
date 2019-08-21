import weka.core.Instances;
import weka.core.converters.ConverterUtils;
import weka.core.SerializationHelper;
import weka.classifiers.Classifier;
import java.io.FileWriter;
import org.apache.commons.math3.complex.Complex;
import org.apache.commons.math3.transform.TransformType;
import org.apache.commons.math3.transform.FastFourierTransformer;
import org.apache.commons.math3.transform.DftNormalization;
import java.util.Arrays;
import java.util.ArrayList;

// 
// Decompiled by Procyon v0.5.36
// 

public class fitness
{
    static ArrayList<String> walsh_chromos;
    static ArrayList<String> fourier_chromos;
    static int numOfGenes;
    static int walsh_order;
    static int k;
    static int walsh_size;
    
    static int min(final int n, final int n2) {
        return (n < n2) ? n : n2;
    }
    
    static int binomialCoeff(final int n, final int n2) {
        final int[][] array = new int[n + 1][n2 + 1];
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= min(i, n2); ++j) {
                if (j == 0 || j == i) {
                    array[i][j] = 1;
                }
                else {
                    array[i][j] = array[i - 1][j - 1] + array[i - 1][j];
                }
            }
        }
        return array[n][n2];
    }
    
    static int calc_walsh(final ArrayList<Integer> list, int i) {
        int n = 0;
        int n2 = 0;
        final ArrayList<Integer> list2 = new ArrayList<Integer>();
        do {
            list2.add(i % 2);
            i /= 2;
            ++n;
        } while (i != 0);
        for (int j = n - 1; j > -1; --j) {
            n2 += list.get(j) * list2.get(j);
        }
        if (n2 % 2 == 0) {
            return 1;
        }
        return -1;
    }
    
    public static void walsh_transform(final String[] array) {
        final ArrayList<Integer> list = new ArrayList<Integer>();
        for (int i = 0; i < array.length; ++i) {
            list.clear();
            for (int j = 0; j < array[i].length(); ++j) {
                list.add(array[i].charAt(j) - '0');
            }
            final int n = 1;
            final int numOfGenes = fitness.numOfGenes;
            int binomialCoeff = binomialCoeff(fitness.numOfGenes, 2);
            int binomialCoeff2 = binomialCoeff(fitness.numOfGenes, 3);
            final int[] array2 = new int[numOfGenes];
            final int[] array3 = new int[binomialCoeff];
            final int[] array4 = new int[binomialCoeff2];

             if (fitness.walsh_order <= 2) {
                binomialCoeff2 = 0;
            }
            if (fitness.walsh_order <= 1) {
                binomialCoeff = 0;
            }

            final int[] a = new int[n + numOfGenes + binomialCoeff + binomialCoeff2];

            for (int k = 0; k < fitness.numOfGenes; ++k) {
                array2[k] = (int)Math.pow(2.0, k);
            }
            int n2 = 0;
            for (int l = 0; l < fitness.numOfGenes; ++l) {
                for (int n3 = l + 1; n3 < fitness.numOfGenes; ++n3) {
                    array3[n2] = array2[l] + array2[n3];
                    ++n2;
                }
            }
            int n4 = 0;
            for (int n5 = 0; n5 < fitness.numOfGenes; ++n5) {
                for (int n6 = n5 + 1; n6 < fitness.numOfGenes; ++n6) {
                    for (int n7 = n6 + 1; n7 < fitness.numOfGenes; ++n7) {
                        array4[n4] = array2[n5] + array2[n6] + array2[n7];
                        ++n4;
                    }
                }
            }
            int n8 = 0;
            a[n8++] = calc_walsh(list, 0);
            for (int n9 = 0; n9 < numOfGenes; ++n9) {
                a[n8++] = calc_walsh(list, array2[n9]);
            }
            for (int n10 = 0; n10 < binomialCoeff; ++n10) {
                a[n8++] = calc_walsh(list, array3[n10]);
            }
            for (int n11 = 0; n11 < binomialCoeff2; ++n11) {
                a[n8++] = calc_walsh(list, array4[n11]);
            }
            fitness.walsh_chromos.add(Arrays.toString(a));
        }
    }
    
    public static void fourier_transform(final String[] array) {
        final double[] array2 = new double[fitness.numOfGenes];
        for (int i = 0; i < array.length; ++i) {
            final String[] split = array[i].split(",");
            for (int j = 0; j < fitness.numOfGenes; ++j) {
                array2[j] = Double.parseDouble(split[j]);
            }
            final Complex[] transform = new FastFourierTransformer(DftNormalization.STANDARD).transform(array2, TransformType.FORWARD);
            String concat = "";
            for (int k = 0; k < transform.length; ++k) {
                concat = concat.concat(Double.toString(transform[k].getReal()));
            }
            fitness.fourier_chromos.add(concat);
        }
    }
    
    public static int getCoeff(final int n, final int n2) {
        if (n2 == 0) {
            return 1 + binomialCoeff(n, 1);
        }
        if (n2 == 1) {
            return 1 + binomialCoeff(n, 1) + binomialCoeff(n, 2);
        }
        if (n2 == 2) {
            return 1 + binomialCoeff(n, 1) + binomialCoeff(n, 2) + binomialCoeff(n, 3);
        }
        return -1;
    }
    
    public static void main(final String[] array) {
        try {
            final String[] split = array[0].split("/");
            final String s = array[1]; // nk
            final String s2 = array[2]; // 10
            final String s3 = array[3]; // 2
            final String s4 = array[4]; // walsh
            final String str = array[5]; // svr

            fitness.numOfGenes = Integer.parseInt(s2);
            fitness.k = Integer.parseInt(s3);
            fitness.walsh_order = fitness.k + 1;
            fitness.walsh_size = getCoeff(fitness.numOfGenes, fitness.k);
            String s5;
            if (fitness.k == -1) {
                s5 = "/home/dong/190806/data/" + s + "_" + s4 + "/" + str + "_" + s4 + "_model/" + s4 + "_" + s + s2 + ".model";
            }
            else {
                s5 = "/home/dong/190806/data/" + s + "_" + s4 + "/" + str + "_" + s4 + "_model/" + str + s2 + "_" + fitness.k + ".model";
            }
            final FileWriter fileWriter = new FileWriter("data.arff");
            fileWriter.write("@relation " + s + "_" + s4 + s2 + "_" + s3 + "\n");
            fileWriter.write("\n");
            if (s4.equals("walsh")) {
                for (int i = 0; i < fitness.walsh_size; ++i) {
                    fileWriter.write("@attribute f" + String.valueOf(i) + " numeric");
                    fileWriter.write("\n");
                }
            }
            else {
                for (int j = 0; j < fitness.numOfGenes; ++j) {
                    fileWriter.write("@attribute f" + String.valueOf(j) + " numeric");
                    fileWriter.write("\n");
                }
            }
            fileWriter.write("@attribute fit numeric\n\n");
            fileWriter.write("@data\n");
            if (s4.equals("fourier")) {
                //System.out.println("fourier");
                fourier_transform(split);
                for (int k = 0; k < split.length; ++k) {
                    fileWriter.write(fitness.fourier_chromos.get(k));
                    fileWriter.write(",");
                    fileWriter.write(" 0\n");
                }
            }
            else if (s4.equals("walsh")) {
                walsh_transform(split);
                //System.out.println("walsh");
                for (int l = 0; l < split.length; ++l) {
                    final String replace = fitness.walsh_chromos.get(l).replace("[", "").replace("]", "");
                    fileWriter.write(replace);
                    fileWriter.write(",");
                    fileWriter.write(" 0\n");
                }
            }
            else {
                //System.out.println("normal");
                for (int n = 0; n < split.length; ++n) {
                    fileWriter.write(split[n]);
                    fileWriter.write(",");
                    fileWriter.write(" 0\n");
                }
            }
            fileWriter.close();
            final Classifier x = (Classifier)SerializationHelper.read(s5);
            final Instances dataSet = new ConverterUtils.DataSource("data.arff").getDataSet();
            final FileWriter fileWriter2 = new FileWriter("result");
            for (int n2 = 0; n2 < dataSet.numInstances(); ++n2) {
                fileWriter2.write(new Double(x.classifyInstance(dataSet.instance(n2))).toString() + " ");
            }
            fileWriter2.close();
        }
        catch (Exception x2) {
            System.out.println(x2);
        }
    }
    
    static {
        fitness.walsh_chromos = new ArrayList<String>();
        fitness.fourier_chromos = new ArrayList<String>();
        fitness.numOfGenes = 0;
        fitness.walsh_order = 0;
        fitness.k = 0;
        fitness.walsh_size = 0;
    }
}
