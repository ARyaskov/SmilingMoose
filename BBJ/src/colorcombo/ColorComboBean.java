package colorcombo;
 
import java.awt.*;
import java.awt.event.*;
import java.awt.event.ActionListener;
import javax.swing.*;
import javax.swing.event.ListDataEvent;
import javax.swing.event.PopupMenuListener;
import javax.accessibility.AccessibleContext;
import java.util.Vector;
import javax.swing.JComboBox;
import javax.swing.plaf.ComboBoxUI;

/* Wrapper class for ColorComboBox */
public final class ColorComboBean extends JPanel {
    
    private ColorComboBox mComboBox;
    
    public void ColorComboBean(){
       mComboBox = new ColorComboBox();
       this.add(mComboBox, BorderLayout.CENTER);
       this.repaint();
    }
    
    public ColorComboBean(Color[] items) 
    {

       mComboBox = new ColorComboBox(items);
       this.add(mComboBox, BorderLayout.CENTER);
       this.repaint();
    }
    public ColorComboBean(Vector items) {
       mComboBox = new ColorComboBox(items);
       this.add(mComboBox, BorderLayout.CENTER);
       this.repaint();
    }

    @Override
    public void setPreferredSize(Dimension preferredSize) {
        mComboBox.setPreferredSize(preferredSize);
    }

   public void actionPerformed(ActionEvent e){
       mComboBox.actionPerformed(e);
   }
   
   public void addActionListener(ActionListener l){
       mComboBox.addActionListener(l);
   }
   public void addFocusListener(FocusListener l){
       mComboBox.addFocusListener(l);
   }
   public void addItem(Color color){
       mComboBox.addItem((Color)color);
   }
    
   public void addItemListener(ItemListener aListener){
       mComboBox.addItemListener(aListener);
   }

   public void addMouseListener(MouseListener l){
       mComboBox.addMouseListener(l);
   }
   public void addPopupMenuListener(PopupMenuListener l){
       mComboBox.addPopupMenuListener(l);
   }

   public void contentsChanged(ListDataEvent e){
       mComboBox.contentsChanged(e);
   }
   public void firePopupMenuCanceled(){
       mComboBox.firePopupMenuCanceled();
   }

   public void firePopupMenuWillBecomeInvisible(){
       mComboBox.firePopupMenuWillBecomeInvisible() ;
   }
   
   public void firePopupMenuWillBecomeVisible(){
       mComboBox.firePopupMenuWillBecomeVisible();
   }

    @Override
   public AccessibleContext getAccessibleContext(){
       return mComboBox.getAccessibleContext();
   } 
   public Action getAction() {
       return mComboBox.getAction();
   }

 public ActionListener[] getActionListeners() {
     return mComboBox.getActionListeners();
 }

 public Color getItemAt(int index){
     return (Color)mComboBox.getItemAt(index);
 }

 public int getItemCount(){
     return mComboBox.getItemCount();
 }

 public ItemListener[] getItemListeners() {
     return mComboBox.getItemListeners();
 }
 public JComboBox.KeySelectionManager getKeySelectionManager(){
     return mComboBox.getKeySelectionManager();
 }

 public int getMaximumRowCount() {
     return mComboBox.getMaximumRowCount();
 }

 public PopupMenuListener[] getPopupMenuListeners()  {
     return mComboBox.getPopupMenuListeners();
 }
 public Object getPrototypeDisplayValue(){
     return mComboBox.getPrototypeDisplayValue();
 }
 public int getSelectedIndex(){
     return mComboBox.getSelectedIndex();
 }
 public Color getSelectedItem() {
     return (Color)mComboBox.getSelectedItem();
 }
 public Color[] getSelectedObjects() {
     return (Color[])mComboBox.getSelectedObjects();
 }
 public void hidePopup(){
     mComboBox.hidePopup();
 }
 public void insertItemAt(Color anColor, int index) {
     mComboBox.insertItemAt(anColor, index);
 }
 public void intervalAdded(ListDataEvent e){
     mComboBox.intervalAdded(e);
 }
 public void intervalRemoved(ListDataEvent e){
     mComboBox.intervalRemoved(e);
 }
 public boolean isLightWeightPopupEnabled() {
     return mComboBox.isLightWeightPopupEnabled();
 }
 public boolean isPopupVisible(){
     return mComboBox.isPopupVisible();
 } 
 @Override
 public void processKeyEvent(KeyEvent e){
      mComboBox.processKeyEvent(e);
 }
 public void removeActionListener(ActionListener l){
     mComboBox.removeActionListener(l);
 } 
 public void removeAllItems(){
     mComboBox.removeAllItems();
 }
 public void removeItem(Color anColor){
     mComboBox.removeItem(anColor);
 }
 public void removeItemAt(int anIndex){
     mComboBox.removeItemAt(anIndex);
 }
 public void removeItemListener(ItemListener aListener){
     mComboBox.removeItemListener(aListener);
 }
 public void removeMouseListener(MouseListener l){
     mComboBox.removeMouseListener(l);
 }
 public void removeFocusListener(FocusListener l){
     mComboBox.removeFocusListener(l);
 }
 public boolean selectWithKeyChar(char keyChar){
     return mComboBox.selectWithKeyChar(keyChar);
 }
 public void setAction(Action a){
     mComboBox.setAction(a);
 }
 public void setActionCommand(String aCommand){
     mComboBox.setActionCommand(aCommand);
 }
    @Override
 public void setEnabled(boolean b){
     mComboBox.setEnabled(b);
 } 
 public void setKeySelectionManager(JComboBox.KeySelectionManager aManager){
     mComboBox.setKeySelectionManager(aManager);
 }
 public void setLightWeightPopupEnabled(boolean aFlag){
     mComboBox.setLightWeightPopupEnabled(aFlag);
 }
 public void setMaximumRowCount(int count){
     mComboBox.setMaximumRowCount(count);
 }
 public void setPopupVisible(boolean v){
     mComboBox.setPopupVisible(v);
 }
 public void setPrototypeDisplayValue(Object prototypeDisplayValue){
     mComboBox.setPrototypeDisplayValue(prototypeDisplayValue);
 } 
 public void setSelectedIndex(int anIndex){
     mComboBox.setSelectedIndex(anIndex);
 }
 public void setSelectedItem(Color item){
     mComboBox.setSelectedItem(item);
 }
 public void setUI(ComboBoxUI ui){
     mComboBox.setUI(ui);
 }
 public void showPopup(){
     mComboBox.showPopup();
 }

}