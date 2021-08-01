#include <iostream>

#include "matrix.cpp"
using namespace std;
double sigmoid(double x){
    return (1/(1+exp(-x)));
}
double dsigmoid(double y){
    //return sigmoid(x)*(1-sigmoid(x));
    return y*(1-y);
}

class NeuralNetwork{
    public:
        int input_nodes;
        int hidden_nodes;
        int output_nodes;
        double learningrate;
        Matrix weights_ih;
        Matrix weights_ho;
        Matrix bias_h;
        Matrix bias_o;
        NeuralNetwork(int numI,int numH,int numO){
        input_nodes =numI;
        hidden_nodes=numH;
        output_nodes=numO;
        learningrate=0.5;
        weights_ih.resize1(hidden_nodes,input_nodes);
        weights_ho.resize1(output_nodes,hidden_nodes);
        bias_h.resize1(hidden_nodes,1);//check if i need to randomize it //CHECKED I NEED//
        bias_o.resize1(output_nodes,1);//check if i need to randomize it //CHECKED I NEED//
        }
        vector <vector<double>> feedforward(double input[]){
            //Generate Hidden layer
            Matrix inputs = Matrix::fromarray(input,input_nodes);
            Matrix hidden =Matrix::multiply(weights_ih,inputs);
            hidden.map1(sigmoid);
            Matrix output =Matrix::multiply(weights_ho,hidden);
            output.add(bias_o);
            output.map1(sigmoid);
            return output.data;
        }
        void train(double input[], double target[]){
            Matrix inputs = Matrix::fromarray(input,input_nodes);
            Matrix hidden = Matrix::multiply(weights_ih,inputs);
            hidden.map1(sigmoid);
            Matrix outputs =Matrix::multiply(weights_ho,hidden);
            outputs.add(bias_o);
            outputs.map1(sigmoid);
            //Matrix outputs= Matrix::fromarray(feedforward(inputs));
            //cerr<<"Output generated\n";
            Matrix targets=Matrix::fromarray(target,output_nodes);
            //cerr<<"Targets Generated\n";
            Matrix errorofuotput=Matrix::subtract(targets,outputs);
            
            Matrix gradients = Matrix::map1(outputs,dsigmoid);
            gradients.multiply(errorofuotput);
            gradients.multiply(learningrate);//TO DO learning_rate
            

            Matrix hidden_T = Matrix::transpose(hidden);
            Matrix weight_ho_deltas = Matrix::multiply(gradients,hidden_T);
            
            weights_ho.add(weight_ho_deltas);
            bias_o.add(gradients);
            
            
            //cerr<<"ErrorOfOutputs generated\n";
            Matrix who_t =Matrix::transpose(weights_ho);
            Matrix hidden_errors = Matrix::multiply(who_t,errorofuotput);
            
            Matrix hidden_gradient = Matrix::map1(hidden,dsigmoid);
            hidden_gradient.multiply(hidden_errors);
            hidden_gradient.multiply(learningrate);

            Matrix inputs_t = Matrix::transpose(inputs);
            Matrix weight_ih_deltas =Matrix::multiply(hidden_gradient,inputs_t);

            weights_ih.add(weight_ih_deltas); 
            bias_h.add(hidden_gradient);
            //outputs.print();
            //targets.print();
            //weights_ih.print();

        return;

        }
};