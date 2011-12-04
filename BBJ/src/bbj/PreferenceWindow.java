/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;
import colorcombo.*;

import javax.swing.*;
import java.awt.*;
import javax.swing.border.*;
import java.awt.event.*;
import javax.swing.BorderFactory;
import javax.swing.event.*;
import java.util.*;

/**
 *
 * @author Lemon
 */
public final class PreferenceWindow extends JDialog 
    implements ItemListener{
    JPanel paneGrid;
    JCheckBox gridDisplay;
    JLabel gridColorLabel;
    JLabel gridFactorLabel;
    JPanel flowPanel1;
    JPanel flowPanel2;
    JPanel flowPanel3;
    ColorComboBean colorCombo;
    
    
    Scene scene;
    JSpinner gridFactorSpinner;
    Vector gridColors;
    
    public PreferenceWindow(){
        
    }
    public PreferenceWindow(Frame f, String title, boolean isModal){
        super(f,title,isModal);
        this.setResizable(false);
        scene = BBJ.app.getScene();
        setSize(new Dimension(500, 300));
        gridColors = new Vector(2);
        gridColors.add(new Color(128,128,128,64));
        gridColors.add(new Color(204,255,243));
        gridColors.add(new Color(204,241,255));
        gridColors.add(new Color(204,216,255));
        gridColors.add(new Color(216,255,204));
        gridColors.add(new Color(204,255,218));
        gridColors.add(new Color(143,255,229));
        gridColors.add(new Color(241,255,204));
        gridColors.add(new Color(255,243,204));
        gridColors.add(new Color(255,218,204));
        
        
        fillGUIContent();
        
    }
    public void fillGUIContent(){

       /* GridLayout layout = new GridLayout(2,2);
        this.getContentPane().setLayout(layout);
        
        paneGrid = new JPanel();
        TitledBorder gridBorder = BorderFactory.createTitledBorder(
                BorderFactory.createLineBorder(Color.BLACK),"Сетка",
                TitledBorder.CENTER, TitledBorder.DEFAULT_POSITION,
                BBJ.borderTitleFont );
        paneGrid.setBorder(gridBorder);
        this.add(paneGrid);*/
       JTabbedPane tabbedPane = new JTabbedPane();
     

       JComponent panel1 = makeDrawPrefs();
       tabbedPane.addTab("Отрисовка", panel1);
       tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);

       tabbedPane.setFont(BBJ.tabTitleFont);
       this.add(tabbedPane);

    }
    
     protected JComponent makeDrawPrefs() {
        JPanel drawPrefsPanel = new JPanel(false);
      
        drawPrefsPanel.setSize(getSize());
        TitledBorder border = new TitledBorder(
                BorderFactory.createRaisedBevelBorder(),"Сетка",TitledBorder.CENTER,
                TitledBorder.DEFAULT_POSITION);
        border.setTitleFont(BBJ.borderTitleFont);
        JPanel gridPrefsPanel = new JPanel();
        BoxLayout boxlayout = new BoxLayout(gridPrefsPanel, BoxLayout.Y_AXIS);
        gridPrefsPanel.setLayout(boxlayout);
 
        gridPrefsPanel.setBorder(border);
        
        gridDisplay = new JCheckBox("Отображать сетку");
        FlowLayout flow1 = new FlowLayout();
        flow1.addLayoutComponent("gridDisplay", gridDisplay);
        gridDisplay.setSelected(scene.getIsGrid());
        gridDisplay.setFont(BBJ.commonArial);
        gridDisplay.addItemListener(this);
       
        gridPrefsPanel.add(gridDisplay);
        
        
        

        // Добавим Spinner для величины ячеек в сетке
        SpinnerModel model =
            new SpinnerNumberModel(scene.getGridFactor(), //initial value
                               5, //min
                               30, //max
                               1); 
        gridFactorSpinner = new JSpinner(model);
        gridFactorSpinner.setPreferredSize(new Dimension(50,22));

        ChangeListener gridFactorListener = new ChangeListener() {
          public void stateChanged(ChangeEvent e) {
              int curVal = Integer.parseInt(
                      gridFactorSpinner.getModel().getValue().toString()
                      );
              scene.setGridFactor(curVal);
          }
        };
        gridFactorSpinner.addChangeListener(gridFactorListener);
        
        gridFactorLabel = new JLabel("Размер ячейки");
        
        flowPanel2 = new JPanel();
        FlowLayout flow2 = new FlowLayout();
        flowPanel2.setLayout(flow2);
        flow2.addLayoutComponent("gridFactorLabel", gridFactorLabel);
        flow2.addLayoutComponent("gridFactorSpinner", gridFactorSpinner);
        
        flowPanel2.add(gridFactorLabel);
        flowPanel2.add(gridFactorSpinner);
        
                
        gridPrefsPanel.add(flowPanel2);
        
        // Добавим ColorComboBox для выбора цвета сетки
        

        colorCombo = new ColorComboBean(gridColors);
        colorCombo.setSelectedItem(scene.getGridColor());
        gridPrefsPanel.add(colorCombo);
        
        colorCombo.addItemListener(new ItemListener(){
          public void itemStateChanged(ItemEvent e)
          { Color color = (Color)e.getItem();
            scene.setGridColor(color);
          } });
        
        gridColorLabel = new JLabel("Цвет сетки   ");
        
        flowPanel3 = new JPanel();
        FlowLayout flow3 = new FlowLayout();
        flowPanel3.setLayout(flow3);
        flow3.addLayoutComponent("gridColorLabel", gridColorLabel);
        flow3.addLayoutComponent("colorCombo", colorCombo);
        
        flowPanel3.add(gridColorLabel);
        flowPanel3.add(colorCombo);
        
        gridPrefsPanel.add(flowPanel3);
        
        
        drawPrefsPanel.add(gridPrefsPanel);
        return drawPrefsPanel;
    }
     

     
     
  public void itemStateChanged(ItemEvent e) {
   
    Object source = e.getItemSelectable();
    
    if (source == gridDisplay && e.getStateChange() == ItemEvent.DESELECTED) {
        scene.setIsGrid(false);
        gridFactorLabel.setEnabled(false);
        gridFactorSpinner.setEnabled(false);
        gridColorLabel.setEnabled(false);
        colorCombo.setEnabled(false);
    }else if (source == gridDisplay && e.getStateChange() == ItemEvent.SELECTED){
        scene.setIsGrid(true);
        gridFactorLabel.setEnabled(true);
        gridFactorSpinner.setEnabled(true);
        gridColorLabel.setEnabled(true);
        colorCombo.setEnabled(true);
    }
    
    if (source == gridFactorSpinner){
        
    }
        
 
}
     
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = BBJ.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }
}
