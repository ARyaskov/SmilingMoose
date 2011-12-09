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
        implements ItemListener {

    JPanel paneGrid;
    JCheckBox gridDisplay;
    JLabel gridColorLabel;
    JLabel gridFactorLabel;
    JPanel flowPanel1;
    JPanel flowPanel2;
    JPanel flowPanel3;
    ColorComboBean colorCombo;
    JCheckBox qualityAntialiasing;
    JCheckBox qualityTextAntialiasing;
    JCheckBox qualityInterpolation;
    JComboBox comboRenderQuality;
    JComboBox comboAlpha;
    Scene scene;
    JSpinner gridFactorSpinner;
    Vector gridColors;

    public PreferenceWindow() {
    }

    public PreferenceWindow(Frame f, String title, boolean isModal) {
        super(f, title, isModal);
        this.setResizable(false);
        scene = BBJ.app.getScene();
        setSize(new Dimension(500, 500));
        gridColors = new Vector();
        gridColors.add(new Color(128, 128, 128, 64));
        gridColors.add(new Color(204, 255, 243));
        gridColors.add(new Color(204, 241, 255));
        gridColors.add(new Color(204, 216, 255));
        gridColors.add(new Color(216, 255, 204));
        gridColors.add(new Color(204, 255, 218));
        gridColors.add(new Color(143, 255, 229));
        gridColors.add(new Color(241, 255, 204));
        gridColors.add(new Color(255, 243, 204));
        gridColors.add(new Color(255, 218, 204));


        fillGUIContent();

    }

    public void fillGUIContent() {

        /*
         * GridLayout layout = new GridLayout(2,2);
         * this.getContentPane().setLayout(layout);
         *
         * paneGrid = new JPanel(); TitledBorder gridBorder =
         * BorderFactory.createTitledBorder(
         * BorderFactory.createLineBorder(Color.BLACK),"Сетка",
         * TitledBorder.CENTER, TitledBorder.DEFAULT_POSITION,
         * BBJ.borderTitleFont ); paneGrid.setBorder(gridBorder);
        this.add(paneGrid);
         */
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
                BorderFactory.createRaisedBevelBorder(), "Сетка", TitledBorder.CENTER,
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
        gridFactorSpinner.setPreferredSize(new Dimension(50, 22));

        ChangeListener gridFactorListener = new ChangeListener() {

            public void stateChanged(ChangeEvent e) {
                int curVal = Integer.parseInt(
                        gridFactorSpinner.getModel().getValue().toString());
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

        colorCombo.addItemListener(new ItemListener() {

            public void itemStateChanged(ItemEvent e) {
                Color color = (Color) e.getItem();
                scene.setGridColor(color);
            }
        });

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



        // ==== Следующая секция - качество отрисовки

        JPanel qualityPrefsPanel = new JPanel();
        BoxLayout qltLayout = new BoxLayout(qualityPrefsPanel, BoxLayout.Y_AXIS);
        qualityPrefsPanel.setLayout(qltLayout);
        TitledBorder borderQuality = new TitledBorder(
                BorderFactory.createRaisedBevelBorder(), "Качество отрисовки", TitledBorder.CENTER,
                TitledBorder.DEFAULT_POSITION);
        border.setTitleFont(BBJ.borderTitleFont);
        qualityPrefsPanel.setBorder(borderQuality);
        borderQuality.setTitleFont(BBJ.borderTitleFont);

        qualityAntialiasing = new JCheckBox("Улучшенное сглаживание");
        qualityAntialiasing.addItemListener(this);
        qualityAntialiasing.setSelected(
                BBJ.qltAntialiasing == RenderingHints.VALUE_ANTIALIAS_OFF
                ? false : true);
        qualityAntialiasing.setFont(BBJ.commonArial);
        qualityPrefsPanel.add(qualityAntialiasing);


        qualityTextAntialiasing = new JCheckBox("Улучшенное сглаживание текста");
        qualityTextAntialiasing.addItemListener(this);
        qualityTextAntialiasing.setSelected(
                BBJ.qltTextAntialiasing1 == RenderingHints.VALUE_TEXT_ANTIALIAS_DEFAULT
                ? false : true);
        qualityTextAntialiasing.setFont(BBJ.commonArial);
        qualityPrefsPanel.add(qualityTextAntialiasing);


        qualityInterpolation = new JCheckBox("Улучшенная интерполяция");
        qualityInterpolation.addItemListener(this);
        qualityInterpolation.setSelected(
                BBJ.qltInterpolation == RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR
                ? false : true);
        qualityInterpolation.setFont(BBJ.commonArial);
        qualityPrefsPanel.add(qualityInterpolation);

        /*
         * JLabel labelRenderQuality = new JLabel("Отрисовка "); JPanel
         * tempPanel = new JPanel(); tempPanel.setLayout(new
         * BoxLayout(tempPanel,BoxLayout.LINE_AXIS));
         * tempPanel.add(labelRenderQuality); Vector tempVector1 = new Vector();
         * tempVector1.add("Скорость"); tempVector1.add("Качество");
         * comboRenderQuality = new JComboBox(tempVector1);
         * comboRenderQuality.addItemListener(this);
         * comboRenderQuality.setSelectedItem( BBJ.qltRender1 ==
         * RenderingHints.VALUE_RENDER_DEFAULT ? "Скорость" : "Качество");
         * comboRenderQuality.setFont(BBJ.commonArial);
         * tempPanel.add(comboRenderQuality); qualityPrefsPanel.add(tempPanel);
         *
         * JLabel spacer = new JLabel(" "); JPanel tempPanel3 = new JPanel();
         * tempPanel3.setLayout(new BoxLayout(tempPanel3,BoxLayout.LINE_AXIS));
         * tempPanel3.add(spacer); qualityPrefsPanel.add(tempPanel3);
         *
         * JLabel labelAlpha = new JLabel("Прозрачность "); JPanel tempPanel2 =
         * new JPanel(); tempPanel2.setLayout(new
         * BoxLayout(tempPanel2,BoxLayout.LINE_AXIS));
         * tempPanel2.add(labelAlpha); comboAlpha = new JComboBox(tempVector1);
         * comboAlpha.setSelectedItem( BBJ.qltAlphaInterpolation ==
         * RenderingHints.VALUE_ALPHA_INTERPOLATION_SPEED ? "Скорость" :
         * "Качество"); comboAlpha.addItemListener(this);
         * comboAlpha.setFont(BBJ.commonArial); tempPanel2.add(comboAlpha);
         * qualityPrefsPanel.add(tempPanel2);
         */


        drawPrefsPanel.add(qualityPrefsPanel);

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
        } else if (source == gridDisplay && e.getStateChange() == ItemEvent.SELECTED) {
            scene.setIsGrid(true);
            gridFactorLabel.setEnabled(true);
            gridFactorSpinner.setEnabled(true);
            gridColorLabel.setEnabled(true);
            colorCombo.setEnabled(true);
        }

        if (source == qualityAntialiasing && e.getStateChange() == ItemEvent.DESELECTED) {
            BBJ.qltAntialiasing = RenderingHints.VALUE_ANTIALIAS_OFF;
        } else if (source == qualityAntialiasing && e.getStateChange() == ItemEvent.SELECTED) {
            BBJ.qltAntialiasing = RenderingHints.VALUE_ANTIALIAS_ON;
        }
        if (source == qualityTextAntialiasing && e.getStateChange() == ItemEvent.DESELECTED) {
            BBJ.qltTextAntialiasing1 = RenderingHints.VALUE_TEXT_ANTIALIAS_DEFAULT;
            BBJ.qltTextAntialiasing2 = null;
            BBJ.qltTextAntialiasing3 = null;
            BBJ.qltTextAntialiasing4 = null;
        } else if (source == qualityTextAntialiasing && e.getStateChange() == ItemEvent.SELECTED) {
            BBJ.qltTextAntialiasing1 = RenderingHints.VALUE_TEXT_ANTIALIAS_ON;
            //BBJ.qltTextAntialiasing2 = RenderingHints.VALUE_TEXT_ANTIALIAS_GASP;
            BBJ.qltTextAntialiasing3 = RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB;
            // BBJ.qltTextAntialiasing4 = RenderingHints.VALUE_FRACTIONALMETRICS_ON;
        }
        if (source == qualityInterpolation && e.getStateChange() == ItemEvent.DESELECTED) {
            BBJ.qltInterpolation = RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR;
        } else if (source == qualityInterpolation && e.getStateChange() == ItemEvent.SELECTED) {
            BBJ.qltInterpolation = RenderingHints.VALUE_INTERPOLATION_BICUBIC;
        }
        /*
         * if (source == comboRenderQuality &&
         * "Скорость".equals(e.getItem().toString())){ BBJ.qltRender1 =
         * RenderingHints.VALUE_RENDER_DEFAULT; BBJ.qltRender2 =
         * RenderingHints.VALUE_DITHER_DISABLE; BBJ.qltRender3 =
         * RenderingHints.VALUE_COLOR_RENDER_SPEED; BBJ.qltRender4 =
         * RenderingHints.VALUE_STROKE_PURE; }else if (source ==
         * comboRenderQuality && "Качество".equals(e.getItem().toString())){
         * BBJ.qltRender1 = RenderingHints.VALUE_RENDER_QUALITY; BBJ.qltRender2
         * = RenderingHints.VALUE_DITHER_ENABLE; BBJ.qltRender3 =
         * RenderingHints.VALUE_COLOR_RENDER_QUALITY; BBJ.qltRender4 =
         * RenderingHints.VALUE_STROKE_NORMALIZE; } if (source == comboAlpha &&
         * "Скорость".equals(e.getItem().toString())){ BBJ.qltAlphaInterpolation
         * = RenderingHints.VALUE_ALPHA_INTERPOLATION_SPEED; }else if (source ==
         * comboAlpha && "Качество".equals(e.getItem().toString())){
         * BBJ.qltAlphaInterpolation =
         * RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY; }
         */
        BBJ.app.mainFrame.repaint();
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
