module.exports = function(sequelize, DataTypes){
	return sequelize.define("Invoice",{
		id: { type: Sequelize.INTEGER, autoIncrement: true },
		rent_start: {type: Sequelize.DATE, allowNull:false},
		rent_end: {type: Sequelize.DATE, allowNull:true},
		saldo: { type: Sequelize.STRING, allowNull: true},
	})
}
