void yield_xgt1(UInt_t runNum, Int_t numEvents)
{

  TFile *replayFile = new TFile(Form("/net/cdaqfs/home/cdaq/hallc-online/hallc_replay/ROOTfiles/shms_replay_production_%d_%d.root", runNum, numEvents));

  TTree *dataTree = dynamic_cast <TTree*> replayFile->Get("T");

  TCanvas *can = new TCanvas("can", "x > 1 Canvas", 1600, 800);
  can->Divide(2, 2);

  TCut deltaCut    = "P.gtr.dp > -10.0 && P.gtr.dp < 22.0";
  TCut cerCut      = "P.ngcer.npeSum > 2.0";
  TCut calCut      = "P.cal.etracknorm > 0.8";
  TCut calZeroCut  = "P.cal.etracknorm > 0.0";
  TCut xbjCut      = "P.kin.x_bj > 1.5 && P.kin.x_bj < 1.9";
  //TCut xbjCut      = "P.kin.x_bj < 3.0";
  TCut pidCut      = deltaCut && cerCut && calCut;
  TCut pidNoCalCut = deltaCut && cerCut && calZeroCut;
  TCut allCuts     = pidCut && xbjCut;
  
  TH1F *xbjHisto     = new TH1F("xbjHisto", "SHMS Bjorken x; x_{Bj}; Number of Entries", 300, 0.0, 3.0);
  TH1F *q2Histo      = new TH1F("q2Histo", "SHMS Q^{2}; Q^{2} (GeV^{2}); Number of Entries / 0.010 GeV", 1000, 0.0, 10.0);
  TH1F *w2Histo      = new TH1F("w2Histo", "SHMS W^{2}; W^{2} (GeV^{2}); Number of Entries / 0.010 GeV", 1200, 0.0, 12.0);
  TH1F *etotHisto    = new TH1F("etotHisto", "SHMS Normalized Track Energy; E/P; Number of Entries / 0.010 GeV", 150, 0.0, 1.5);
  TH1F *etotCutHisto = new TH1F("etotCutHisto", "SHMS Normalized Track Energy; E/P; Number of Entries / 0.010 GeV", 150, 0.0, 1.5);
  
  dataTree->Project(xbjHisto->GetName(), "P.kin.x_bj", pidCut);
  dataTree->Project(q2Histo->GetName(), "P.kin.Q2", pidCut);
  dataTree->Project(w2Histo->GetName(), "P.kin.W2", pidCut);
  dataTree->Project(etotHisto->GetName(), "P.cal.etracknorm", pidNoCalCut);
  dataTree->Project(etotCutHisto->GetName(), "P.cal.etracknorm", allCuts);

  Int_t yield   = etotCutHisto->Integral();
  Double_t etotMax = etotCutHisto->GetMaximum();

  gStyle->SetOptStat(0);
  etotHisto->SetLineColor(kRed);
  etotCutHisto->SetLineColor(kBlue);

  TLegend *leg = new TLegend(0.15, 0.6, 0.4, 0.85);
  leg->AddEntry(etotCutHisto, Form("Yield = %d", yield), "");
  leg->SetTextColor(kBlue);
  leg->SetLineColor(0);

  //cout << "Yield = " << yield << endl;

  can->cd(1);
  xbjHisto->Draw();
  can->cd(2);
  q2Histo->Draw();
  can->cd(3);
  w2Histo->Draw();
  can->cd(4);
  etotHisto->Draw();
  etotCutHisto->Draw("SAME");
  leg->Draw();
}
