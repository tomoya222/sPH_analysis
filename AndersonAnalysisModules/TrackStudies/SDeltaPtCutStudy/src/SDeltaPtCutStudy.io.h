// ----------------------------------------------------------------------------
// 'SDeltaPtCutStudy.io.h'
// Derek Anderson
// 07.06.2023
//
// Reads in the 'ntp_track' Ntuple
// generated by the SVtxEvaluator
// class and studies how deltapt/pt
// varies with quality cuts.
// ----------------------------------------------------------------------------

#pragma once

using namespace std;



// public io methods ----------------------------------------------------------

void SDeltaPtCutStudy::SetInputOutputFiles(const TString sInput, const TString sOutput) {

  sInFile  = sInput;
  sOutFile = sOutput;
  cout << "    Set input/output files:\n"
       << "      input  = " << sInFile.Data() << "\n"
       << "      output = " << sOutFile.Data()
       << endl;
  return;

}  // end 'SetInputOutputFiles(TString, TString)'



void SDeltaPtCutStudy::SetInputTuples(const TString sTrack, const TString sTruth) {

  sInTrack = sTrack;
  sInTruth = sTruth;
  cout << "    Set track/truth tuples:\n"
       << "      track tuple = " << sInTrack.Data() << "\n"
       << "      truth tuple = " << sInTruth.Data()
       << endl;
  return;

}  // end 'SetInputTuples(TString, TString)'



void SDeltaPtCutStudy::SetGeneralTrackCuts(const uint32_t nInttCut, const uint32_t nMvtxCut, const uint32_t nTpcCut, const double qualCut, const double vzCut, const double ptCut) {

  nInttTrkMin = nInttCut;
  nMVtxTrkMin = nMvtxCut;
  nTpcTrkMin  = nTpcCut;
  qualTrkMax  = qualCut;
  vzTrkMax    = vzCut;
  ptTrkMin    = ptCut;
  cout << "    Set general track cuts:\n"
       << "      nIntt   > " << nInttTrkMin << "\n"
       << "      nMvtx   > " << nMVtxTrkMin << "\n"
       << "      nTpc    > " << nTpcTrkMin  << "\n"
       << "      quality < " << qualTrkMax  << "\n"
       << "      |vz|    < " << vzTrkMax    << "\n"
       << "      pt      > " << ptTrkMin
       << endl;
  return;

}  // end 'SetGeneralTrackCuts(uint32_t, uint32_t, uint32_t, double, double, double)'



void SDeltaPtCutStudy::SetSigmaFitGuesses(const array<float, Const::NPar> hiGuess, const array<float, Const::NPar> loGuess) {

  for (uint8_t iPar = 0; iPar < Const::NPar; iPar++) {
    sigHiGuess[iPar] = hiGuess[iPar];
    sigLoGuess[iPar] = loGuess[iPar];
  }
  cout << "    Set sigma(delta-pt / pt) fit guesses:\n"
       << "      high guess parameters = (" << sigHiGuess[0] << ", " << sigHiGuess[1] << ", " << sigHiGuess[2] << ")\n"
       << "      low guess parameters  = (" << sigLoGuess[0] << ", " << sigLoGuess[1] << ", " << sigLoGuess[2] << ")"
      << endl;
  return;

}  // end 'SetSigmaFitGuesses(array<float>, array<float>)'



void SDeltaPtCutStudy::SetNormAndFitRanges(const pair<float, float> norm, const pair<float, float> ptFit, const pair<float, float> deltaFit) {

    normRange[0]     = norm.first;
    normRange[1]     = norm.second;
    ptFitRange[0]    = ptFit.first;
    ptFitRange[1]    = ptFit.second;
    deltaFitRange[0] = deltaFit.first;
    deltaFitRange[1] = deltaFit.second;
    cout << "    Set normalization and fit ranges:\n"
         << "      normalization = (" << normRange[0]     << ", " << normRange[1]     << ")\n"
         << "      pt fit        = (" << ptFitRange[0]    << ", " << ptFitRange[1]    << ")\n"
         << "      delta-pt fit  = (" << deltaFitRange[0] << ", " << deltaFitRange[1] << ")"
         << endl;
    return;

}  // end 'SetNormAndFitRange(pair<float, float>, pair<float, float>, pair<float, float>)'



void SDeltaPtCutStudy::SetPlotRanges(const pair<float, float> ptRange, const pair<float, float> fracRange, const pair<float, float> deltaRange) {

  rPtRange[0]    = ptRange.first;
  rPtRange[1]    = ptRange.second;
  rFracRange[0]  = fracRange.first;
  rFracRange[1]  = fracRange.second;
  rDeltaRange[0] = deltaRange.first;
  rDeltaRange[1] = deltaRange.second;
  cout << "    Set plot ranges:\n"
       << "      pt    = (" << rPtRange[0]    << ", " << rPtRange[1]    << ")\n"
       << "      frac  = (" << rFracRange[0]  << ", " << rFracRange[1]  << ")\n"
       << "      delta = (" << rDeltaRange[0] << ", " << rDeltaRange[1] << ")"
       << endl;
  return;

}  // end 'SetPlotRanges(pair<float, float>, pair<float, float>, pair<float, float>)'



void SDeltaPtCutStudy::SetGeneralStyleParameters(const array<uint32_t, Const::NTypes> arrCol, const array<uint32_t, Const::NTypes> arrMar) {

  fColTrue = arrCol[0];
  fColPure = arrCol[1];
  fColTrk  = arrCol[2];
  fMarTrue = arrMar[0];
  fMarPure = arrMar[1];
  fMarTrk  = arrMar[2];
  cout << "    Set general style parameters:\n"
       << "      colors (true, pure, track)  = (" << fColTrue << ", " << fColPure << ", " << fColTrk << ")\n"
       << "      markers (true, pure, track) = (" << fMarTrue << ", " << fMarPure << ", " << fMarTrk << ")"
       << endl;
  return;

}  // end 'SetGeneralStyleParameters(array<uint32_t>, array<uint32_t>)'



void SDeltaPtCutStudy::SetGeneralHistParameters(const uint32_t fill, const uint32_t line, const uint32_t width, const uint32_t font, const uint32_t align, const uint32_t center) {

  fFil = fill;
  fLin = line;
  fWid = width;
  fTxt = font;
  fAln = align;
  fCnt = center;
  cout << "    Set general histogram parameters:\n"
       << "      fill   = " << fFil << "\n"
       << "      line   = " << fLin << "\n"
       << "      width  = " << fWid << "\n"
       << "      font   = " << fTxt << "\n"
       << "      align  = " << fAln << "\n"
       << "      center = " << fCnt
       << endl;
  return;

}  // end 'SetGeneralHistParameters(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)'



void SDeltaPtCutStudy::SetHistBaseNames(const TString sProj, const TString sDelta, const TString sTrue, const TString sReco, const TString sFrac, const TString sTrack) {

  sPtProjBase   = sProj;
  sPtDeltaBase  = sDelta;
  sPtTrueBase   = sTrue;
  sPtRecoBase   = sReco;
  sPtFracBase   = sFrac;
  sPtTrkTruBase = sTrack;
  cout << "    Set histogram base names:\n"
       << "      " << sPtProjBase   << "\n"
       << "      " << sPtDeltaBase  << "\n"
       << "      " << sPtTrueBase   << "\n"
       << "      " << sPtRecoBase   << "\n"
       << "      " << sPtFracBase   << "\n"
       << "      " << sPtTrkTruBase
       << endl;
  return;

}  // end 'SetHistBaseNames(TString, TString, TString, TString, TString, TString)'



void SDeltaPtCutStudy::SetPlotText(const vector<TString> plotText) {

  nTxt  = plotText.size();
  sInfo = plotText;

  cout << "    Set plot text:" << endl;
  for (size_t iTxt = 0; iTxt < nTxt; iTxt++) {
    cout << "      " << sInfo[iTxt] << endl;
  }
  return;

}  // end 'SetPlotText(vector<TString>)'



void SDeltaPtCutStudy::SetEffRebinParameters(const bool doRebin, const size_t nRebin) {

  doEffRebin = doRebin;
  nEffRebin  = nRebin;
  cout << "    Set efficiency rebinning parameters:\n"
       << "      do rebin? = " << doEffRebin << "\n"
       << "      nRebin    = " << nEffRebin
       << endl;
  return;

}  // end 'SetRebinParameters(bool, size_t)'



void SDeltaPtCutStudy::SetProjectionParameters(const vector<tuple<double, TString, uint32_t, uint32_t, uint32_t>> projParams) {

  nProj = projParams.size();
  for (auto param : projParams) {
    ptProj.push_back(get<0>(param));
    sProjSuffix.push_back(get<1>(param));
    fColProj.push_back(get<2>(param));
    fMarProj.push_back(get<3>(param));
    fColFit.push_back(get<4>(param));
  }

  cout << "    Set projection parameters." << endl;
  return;

}  // end 'SetProjectionParameters(vector<tuple<double, TString, uint32_t, uint32_t, uint32_t>>)'



void SDeltaPtCutStudy::SetFlatCutParameters(const vector<tuple<double, TString, uint32_t, uint32_t, bool>> flatParams) {

  bool   cutSelected = false;
  size_t iParam      = 0;
  for (auto param : flatParams) {

    // read in parameters
    ptDeltaMax.push_back(get<0>(param));
    sDPtSuffix.push_back(get<1>(param));
    fColCut.push_back(get<2>(param));
    fMarCut.push_back(get<3>(param));

    // determine which cut to draw
    if (!cutSelected && get<4>(param)) {
      iCutToDraw  = iParam;
      cutSelected = true;
    }
    ++iParam;
  }
  nDPtCuts = flatParams.size();

  cout << "    Set flat delta-pt cut parameters." << endl; 
  return;

}  // end 'SetFlatCutParameters(vector<tuple<double, TString, uint32_t, uint32_t, bool>>)'



void SDeltaPtCutStudy::SetPtDependCutParameters(const vector<tuple<double, TString, uint32_t, uint32_t, uint32_t, bool>> ptDependParams) {

  bool   cutSelected = false;
  size_t iParam      = 0;
  for (auto param : ptDependParams) {

    // read in parameters
    ptDeltaSig.push_back(get<0>(param));
    sSigSuffix.push_back(get<1>(param));
    fColSig.push_back(get<2>(param));
    fMarSig.push_back(get<3>(param));
    fColSigFit.push_back(get<4>(param));

    // determine which cut to draw
    if (!cutSelected && get<5>(param)) {
      iCutToDraw  = iParam;
      cutSelected = true;
    }
    ++iParam;
  }
  nSigCuts = ptDependParams.size();

  cout << "    Set pt-dependent delta-pt cut parameters." << endl; 
  return;

}  // end 'SetFlatCutParameters(vector<tuple<double, TString, uint32_t, uint32_t, uint32_t, bool>>)'



// private io methods ---------------------------------------------------------

void SDeltaPtCutStudy::OpenFiles() {

  fOutput = new TFile(sOutFile.Data(), "recreate");
  fInput  = new TFile(sInFile.Data(),  "read");
  if (!fInput || !fOutput) {
    cerr << "PANIC: couldn't open a file!\n"
         << "       fInput  = " << fInput  << "\n"
         << "       fOutput = " << fOutput << "\n"
         << endl;
    assert(fOutput && fInput);
  }

  cout << "      Opened files." << endl;
  return;

}  // end 'OpenFiles()'



void SDeltaPtCutStudy::GetTuples() {

  ntTrack = (TNtuple*) fInput -> Get(sInTrack.Data());
  ntTruth = (TNtuple*) fInput -> Get(sInTruth.Data());
  if (!ntTrack || !ntTruth) {
    cerr << "PANIC: couldn't grab aninput tuple!\n"
         << "       ntTrack = " << ntTrack << "\n"
         << "       ntTruth = " << ntTruth << "\n"
         << endl;
    assert(ntTrack && ntTruth);
  }

  cout << "      Grabbed input tuples." << endl;
  return;

}  // 'GetTuples()'



void SDeltaPtCutStudy::SaveOutput() {

  // make directories
  TDirectory *dNoCut    = (TDirectory*) fOutput -> mkdir("NoCuts");
  TDirectory *dFlatCut  = (TDirectory*) fOutput -> mkdir("FlatCuts");
  TDirectory *dSigmaCut = (TDirectory*) fOutput -> mkdir("SigmaCuts");
  TDirectory *dProject  = (TDirectory*) fOutput -> mkdir("Projections");
  cout << "      Made output directories." << endl;

  // save histograms
  fOutput         -> cd();
  dNoCut          -> cd();
  hEff            -> Write();
  hPtTruth        -> Write();
  hPtDelta        -> Write();
  hPtTrack        -> Write();
  hPtFrac         -> Write();
  hPtTrkTru       -> Write();
  hPtDeltaVsFrac  -> Write();
  hPtDeltaVsTrue  -> Write();
  hPtDeltaVsTrack -> Write();
  hPtTrueVsTrack  -> Write();

  // save flat delta-pt cut histograms
  dFlatCut -> cd();
  grRejCut -> Write();
  for (size_t iCut = 0; iCut < nDPtCuts; iCut++) {
    hEffCut[iCut]            -> Write();
    hPtDeltaCut[iCut]        -> Write();
    hPtTrackCut[iCut]        -> Write();
    hPtFracCut[iCut]         -> Write();
    hPtTrkTruCut[iCut]       -> Write();
    hPtDeltaVsFracCut[iCut]  -> Write();
    hPtDeltaVsTrueCut[iCut]  -> Write();
    hPtDeltaVsTrackCut[iCut] -> Write();
    hPtTrueVsTrackCut[iCut]  -> Write();
  }

  // save pt-dependent delta-pt cut histograms
  dSigmaCut -> cd();
  grRejSig  -> Write();
  for (size_t iSig = 0; iSig < nSigCuts; iSig++) {
    hEffSig[iSig]            -> Write();
    hPtDeltaSig[iSig]        -> Write();
    hPtTrackSig[iSig]        -> Write();
    hPtFracSig[iSig]         -> Write();
    hPtTrkTruSig[iSig]       -> Write();
    hPtDeltaVsFracSig[iSig]  -> Write();
    hPtDeltaVsTrueSig[iSig]  -> Write();
    hPtDeltaVsTrackSig[iSig] -> Write();
    hPtTrueVsTrackSig[iSig]  -> Write();
  }

  // save delta-pt projection histograms
  dProject  -> cd();
  grMuProj  -> Write();
  grSigProj -> Write();
  for (size_t iProj = 0; iProj < nProj; iProj++) {
    hPtDeltaProj[iProj] -> Write();
    fPtDeltaProj[iProj] -> Write();
  }
  for (size_t iSig = 0; iSig < nSigCuts; iSig++) {
    fMuHiProj[iSig]  -> Write();
    fMuLoProj[iSig]  -> Write();
    grMuHiProj[iSig] -> Write();
    grMuLoProj[iSig] -> Write();
  }

  cout << "      Saved output." << endl;
  return;

}  // end 'SaveOutput()'



void SDeltaPtCutStudy::CloseFiles() {

  fOutput -> cd();
  fOutput -> Close();
  fInput  -> cd();
  fInput  -> Close();

  cout << "      Closed files." << endl;
  return;

}  // end 'CloseFiles()'

// end ------------------------------------------------------------------------
