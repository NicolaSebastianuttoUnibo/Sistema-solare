void sss() {

    TFile *inputFile = TFile::Open("output.root");

    TH1F *h2 = (TH1F*)inputFile->Get("angoli azitumali");
    TH1F *h3 = (TH1F*)inputFile->Get("angoli polari");
    TH1F *h4 = (TH1F*)inputFile->Get("impulso");
    TH1F *h8 = (TH1F*)inputFile->Get("massa invarianti di particelle discorde");
    TH1F *h9 = (TH1F*)inputFile->Get("massa invarianti di particelle concorde");
    TH1F *h10 = (TH1F*)inputFile->Get("kaone+- pione+- discordi");
    TH1F *h11 = (TH1F*)inputFile->Get("kaone+- pione+- concordi");
    TH1F *h12 = (TH1F*)inputFile->Get("risonanza");





    TF1 *Fit1 = new TF1("uniform1", "pol0", 0, 2*TMath::Pi());
    TF1 *Fit2 = new TF1("uniform2", "pol0", 0, TMath::Pi());
    TF1 *Fit3 = new TF1("exponential", "expo", 0, 1e9*2);
    TF1 *Fit4 = new TF1("gaussian1", "gaus", 0.89166,0.050);
    TF1 *Fit5 = new TF1("gaussian2", "gaus", 0.89166,0.050);
       
   

    h2->Fit(Fit1, "Q");
    std::cout << "Fit per angoli azimutali:" << "\n";
    std::cout << "Parametri: " << Fit1->GetParameter(0) << "\n";
    std::cout << "Chi2/NDF: " << Fit1->GetChisquare() / Fit1->GetNDF() << "\n";
    std::cout << "Probabilità del fit: " << Fit1->GetProb() << "\n\n";

    h3->Fit(Fit2, "Q");
    std::cout << "\nFit per angoli polari:" << "\n";
    std::cout << "Parametri: " << Fit2->GetParameter(0) << "\n";
    std::cout << "Chi2/NDF: " << Fit2->GetChisquare() / Fit2->GetNDF() << "\n";
    std::cout << "Probabilità del fit: " << Fit2->GetProb() << "\n\n";

        h4->Fit(Fit3, "Q");
    std::cout << "\nFit per impulso:" << "\n";
    std::cout << "Parametri: " << Fit3->GetParameter(0) <<", "<<Fit3->GetParameter(1)<< "\n";
    std::cout << "Chi2/NDF: " << Fit3->GetChisquare() / Fit3->GetNDF() << "\n";
    std::cout << "Probabilità del fit: " << Fit3->GetProb() << "\n\n";



h8->Sumw2();
h9->Sumw2();

TH1F *h_diff = (TH1F*)h8->Clone("h_diff");  
h_diff->Add(h9, -1);

h10->Sumw2();
h11->Sumw2();

TH1F *h_diff2 = (TH1F*)h10->Clone("h_diff");  
h_diff2->Add(h11, -1);



    h_diff->Fit(Fit4, "Q");
    std::cout << "Fit per prima differenza:" << "\n";
    std::cout << "Parametri: " << Fit4->GetParameter(0) <<", "<<Fit4->GetParameter(1)<< "\n";
    std::cout << "Chi2/NDF: " << Fit4->GetChisquare() / Fit4->GetNDF() << "\n";
    std::cout << "Probabilità del fit: " << Fit4->GetProb() << "\n\n";

    h_diff2->Fit(Fit5, "Q");
    std::cout << "Fit per seconda differenza:" << "\n";
    std::cout << "Parametri: " << Fit5->GetParameter(0) <<", "<<Fit5->GetParameter(1)<< "\n";
    std::cout << "Chi2/NDF: " << Fit5->GetChisquare() / Fit5->GetNDF() << "\n";
    std::cout << "Probabilità del fit: " << Fit5->GetProb() << "\n\n";


    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600);
    h2->Draw();
   Fit1->Draw("same");
    //canvas->Update();

    TCanvas *canvas2 = new TCanvas("canvas2", "Canvas2", 800, 600);
    h3->Draw();
   Fit2->Draw("same");
  //  canvas2->Update();

    TCanvas *canvas3 = new TCanvas("canvas3", "Canvas3", 800, 600);
    h4->Draw();
   Fit3->Draw("same");
    canvas3->Update();

       TCanvas *canvas4 = new TCanvas("canvas4", "Canvas4", 800, 600);
    h_diff->Draw();
   Fit4->Draw("same");

    // h12->Draw("same");
    canvas4->Update();
       TCanvas *canvas5 = new TCanvas("canvas5", "Canvas5", 800, 600);
    h_diff2->Draw();
   Fit5->Draw("same");

    // h12->Draw("same");
    canvas5->Update();


   // inputFile->Close();

}
