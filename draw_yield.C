void draw_yield(int run)
{

    TFile* file = new TFile(Form("/net/cdaqfs/home/cdaq/hallc-online/hallc_replay/ROOTfiles/hms_replay_production_%d_-1.root", run));
    //  TFile* file = new TFile(Form("/net/cdaqfs/home/cdaq/hallc-online/hallc_replay/ROOTfiles/hms_replay_production_%d_50000.root", run));
  TTree* T = (TTree*)file->Get("T");

  TCut cut0 = "abs(H.gtr.dp)<9";
  TCut cut1 = "abs(H.gtr.dp)<9 && H.cer.npeSum>2. && H.cal.etracknorm>0.7";

  TH1F* h0 = new TH1F("h0","H.cal.etracknorm",150,0,1.5);
  TH1F* h1 = new TH1F("h1","h1",150,0,1.5);

  T->Project(h0->GetName(), "H.cal.etracknorm", cut0);
  T->Project(h1->GetName(), "H.cal.etracknorm", cut1);

  gStyle->SetOptStat(0);

  h0->SetLineColor(kBlue);
  h1->SetLineColor(kRed);
  h0->SetLineWidth(2);
  h1->SetLineWidth(2);

  h0->Draw();
  gPad->SetLogy(1);
  h1->Draw("same");

  double yields = h1->Integral();
  cout << "************ yields = " << yields << " ************" << endl;

  TLegend *leg = new TLegend(0.35,0.75,0.9,0.9);
  leg->AddEntry(h0, "abs(H.gtr.dp)<9", "l");
  leg->AddEntry(h1, "abs(H.gtr.dp)<9 + H.cer.npeSum>2. + H.cal.etracknorm>0.7", "l");
  leg->Draw("same");

}
