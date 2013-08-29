   QuantidadeSalarios = round((pessoas[i].rendaMensal)/SalarioMinimo);


    if(QuantidadeSalarios < 2){
         pessoas[i].RendaFinal = pessoas[i].rendaMensal;
    }else if((QuantidadeSalarios > 2) && (QuantidadeSalarios < 3)){
        pessoas[i].RendaFinal = pessoas[i].rendaMensal + (0.05*pessoas[i].rendaMensal);
    }else if((QuantidadeSalarios > 3) && (QuantidadeSalarios < 5)){
        pessoas[i].RendaFinal = pessoas[i].rendaMensal + (0.10*pessoas[i].rendaMensal);
    }else if((QuantidadeSalarios > 5) && (QuantidadeSalarios < 7)){
        pessoas[i].RendaFinal = pessoas[i].rendaMensal + ((0.15*pessoas[i].rendaMensal);
    }else if(QuantidadeSalarios > 7){
        pessoas[i].RendaFinal = pessoas[i].rendaMensal + ((0.20*pessoas[i].rendaMensal));
    }
    pessoas[i].RendaFinal -= ((((1 - pessoas[i].Ndependentes*0.05))*pessoas[i].RendaFinal));
